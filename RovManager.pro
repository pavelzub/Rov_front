#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T21:02:44
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RovManager
TEMPLATE = app

INCLUDEPATH += $$PWD/SDL-1.2/include/SDL \
    $$PWD/OpenCV/include
LIBS += -L$$PWD/SDL-1.2/bin -lSDL \
    -L$$PWD/OpenCV/lib \
    -lopencv_highgui2413 \
    -lopencv_calib3d2413 \
    -lopencv_contrib2413 \
    -lopencv_core2413 \
    -lopencv_features2d2413 \
    -lopencv_flann2413 \
    -lopencv_gpu2413 \
    -lopencv_imgproc2413 \
    -lopencv_legacy2413 \
    -lopencv_ml2413 \
    -lopencv_nonfree2413 \
    -lopencv_objdetect2413 \
    -lopencv_ocl2413 \
    -lopencv_photo2413 \
    -lopencv_stitching2413 \
    -lopencv_superres2413 \
    -lopencv_video2413 \
    -lopencv_videostab2413

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mainwidget.cpp \
    gamepadmanager.cpp \
    imagedetector.cpp \
    videowidget.cpp \
    usbcamerawidget.cpp \
    ithernetcamerawidget.cpp \
    timerwidget.cpp

HEADERS += \
        mainwindow.hpp \
    mainwidget.hpp \
    gamepadmanager.hpp \
    imagedetector.hpp \
    videowidget.hpp \
    usbcamerawidget.hpp \
    ithernetcamerawidget.hpp \
    timerwidget.hpp
