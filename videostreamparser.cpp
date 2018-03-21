#include "videostreamparser.hpp"
#include <iostream>
#include <queue>
#include <QDate>
#include <QScopedPointer>

VideoStreamParser::VideoStreamParser(QPixmap* pixmap, QString url, bool *enable, QObject *parent) :
    QObject(parent)
{
    _pixmap = pixmap;
    _url = url;
    _enable = enable;
}

void VideoStreamParser::process()
{
    while(!_init()){
        std::cout << "Init error: " << _url.toStdString()  << std::endl;
    }

    *_enable = true;
    emit(repaint());

   for(;;){
        static std::queue<std::pair<int64_t, double> > ptsDb;

        AVPacket pkt;
        av_init_packet(&pkt);
        pkt.data = nullptr;
        pkt.size = 0;

        if (av_read_frame(_mFormatContext, &pkt) < 0){
            std::cout << "Frame error" << std::endl;
            break;
        }

        double tRecv = QDateTime::currentMSecsSinceEpoch();
        if (pkt.stream_index == _mVideoStreamIdx)
        {
          int got_frame = 0;
          auto mFrame = av_frame_alloc();
          avcodec_decode_video2(_mVideoDecodeContext, mFrame, &got_frame, &pkt);

          *_pixmap = frameToQPixmap(mFrame, _dec_ctx);
          emit(repaint());

          av_free_packet(&pkt);
          av_frame_free(&mFrame);
        }
    }

    emit(finished());
}

QPixmap VideoStreamParser::frameToQPixmap(AVFrame* src_frame, AVCodecContext* dec)
{
    AVFrame *pFrameRGB = av_frame_alloc();

    int numBytes= avpicture_get_size(AV_PIX_FMT_RGB24,
          dec->width, dec->height);
    QScopedPointer<const uint8_t> buffer(new uint8_t[numBytes]);

    avpicture_fill((AVPicture*)pFrameRGB, buffer.data(), AV_PIX_FMT_RGB24,
                  dec->width, dec->height);

    int dst_fmt = AV_PIX_FMT_RGB24;
    int dst_w = dec->width;
    int dst_h = dec->height;

    SwsContext *img_convert_ctx_temp;
    img_convert_ctx_temp = sws_getContext(
    dec->width, dec->height,
    dec->pix_fmt,
    dst_w, dst_h, (AVPixelFormat)dst_fmt,
    SWS_BICUBIC, NULL, NULL, NULL);


    QScopedPointer<QImage> myImage(new QImage(dst_w, dst_h, QImage::Format_RGB32));

    sws_scale(img_convert_ctx_temp,
              src_frame->data, src_frame->linesize, 0, dec->height,
              pFrameRGB->data,
              pFrameRGB->linesize);

    uint8_t* src = (uint8_t*)(pFrameRGB->data[0]);
    for (int y = 0; y < dst_h; y++)
    {
        QRgb *scanLine = (QRgb *) myImage->scanLine(y);
        for (int x = 0; x < dst_w; x=x+1)
        {
            scanLine[x] = qRgb(src[3*x], src[3*x+1], src[3*x+2]);
        }
        src += pFrameRGB->linesize[0];
    }

    QPixmap result = QPixmap::fromImage(*myImage);

    sws_freeContext(img_convert_ctx_temp);
    av_frame_free(&pFrameRGB);
    return result;
}

bool VideoStreamParser::_init()
{
    if (avformat_open_input(&_mFormatContext, _url.toStdString().data(), NULL, NULL) < 0)
            return false;

    avformat_find_stream_info(_mFormatContext, nullptr);
    _mVideoStreamIdx = av_find_best_stream(_mFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    AVStream* st = _mFormatContext->streams[_mVideoStreamIdx];

    _dec_ctx = st->codec;
    AVCodec* dec = avcodec_find_decoder(_dec_ctx->codec_id);
    if (dec->capabilities & CODEC_CAP_TRUNCATED)
        _dec_ctx->flags |= CODEC_FLAG_TRUNCATED;
    _dec_ctx->thread_type  = FF_THREAD_SLICE;
    _dec_ctx->thread_count = 1;

    avcodec_open2(_dec_ctx, dec, nullptr);
    AVStream* videoStream = _mFormatContext->streams[_mVideoStreamIdx];
    _mVideoDecodeContext = videoStream->codec;

    _mDataStreamIdx = av_find_best_stream(_mFormatContext, AVMEDIA_TYPE_DATA, -1, -1, nullptr, 0);
    return true;
}
