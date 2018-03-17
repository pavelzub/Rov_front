#include "anuspes.hpp"
#include <iostream>

AnusPes::AnusPes(QPixmap* pixmap, QString url, QObject *parent) :
    QObject(parent)
{
    _pixmap = pixmap;
    _url = url;
}

void AnusPes::process()
{
    AVFormatContext* format_context = NULL;
    if (avformat_open_input(&format_context, _url.toStdString().data(), NULL, NULL) < 0) {
        fprintf(stderr, "ffmpeg: Unable to open input file\n");
        emit(finished());
        return;
    }

    if (avformat_find_stream_info(format_context, NULL) < 0) {
        fprintf(stderr, "ffmpeg: Unable to find stream info\n");
        emit(finished());
        return;
    }

    int video_stream;
    for (video_stream = 0; video_stream < format_context->nb_streams; ++video_stream) {
        if (format_context->streams[video_stream]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            break;
        }
    }
    if (video_stream == format_context->nb_streams) {
        fprintf(stderr, "ffmpeg: Unable to find video stream\n");
        emit(finished());
        return;
    }

    AVCodecContext* codec_context = format_context->streams[video_stream]->codec;
    AVCodec* codec = avcodec_find_decoder(codec_context->codec_id);
    int err = avcodec_open2(codec_context, codec, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to open codec\n");
        emit(finished());
        return;
    }

    struct SwsContext* img_convert_context;
    img_convert_context = sws_getContext(codec_context->width,
                                         codec_context->height,
                                         codec_context->pix_fmt,
                                         codec_context->width,
                                         codec_context->height,
                                         AV_PIX_FMT_RGB24,
                                         SWS_BICUBIC, NULL, NULL, NULL);
    if (img_convert_context == NULL) {
        fprintf(stderr, "Cannot initialize the conversion context\n");
        emit(finished());
        return;
    }

    AVFrame* frame = av_frame_alloc();
    AVPacket packet;
    int i = 0;
    while (av_read_frame(format_context, &packet) >= 0) {
        if (packet.stream_index == video_stream) {
            // Video stream packet
            int frame_finished;
            avcodec_decode_video2(codec_context, frame, &frame_finished, &packet);

            if (frame_finished) {
                std::cout << frame->width << " " << frame->height << std::endl;
                AVFrame* frameRGB = av_frame_alloc();
                avpicture_alloc((AVPicture*)frameRGB,
                                AV_PIX_FMT_RGB24,
                                codec_context->width,
                                codec_context->height);

                sws_scale(img_convert_context,
                          frame->data,
                          frame->linesize, 0,
                          codec_context->height,
                          frameRGB->data,
                          frameRGB->linesize);

                QImage image(frameRGB->data[0],
                             codec_context->width,
                             codec_context->height,
                             frameRGB->linesize[0],
                             QImage::Format_RGB888);
                *_pixmap = QPixmap::fromImage(image);
                emit(repaint());
            }
        }
    }

    sws_freeContext(img_convert_context);

    av_free(frame);
    avcodec_close(codec_context);
    avformat_close_input(&format_context);
    emit(finished());
}
