#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T21:02:44
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RovManager
TEMPLATE = app

INCLUDEPATH += \
    $$PWD/SDL-1.2/include/SDL \
#    $$PWD/SDL/include \
    $$PWD/ffmpeg/include
LIBS += \
    -L$$PWD/SDL-1.2/bin -lSDL \
#    -L$$PWD/SDL -lSDL2 \
    -L$$PWD/ffmpeg/lib \
    -lavcodec \
    -lavdevice \
    -lavutil \
    -lpostproc \
    -lavfilter \
    -lswresample \
    -lavformat \
    -lswscale

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
    video/videowidget.cpp \
    video/usbcamerawidget.cpp \
    timerwidget.cpp \
    video/ethernetcamerawidget.cpp \
    video/videostreamparser.cpp \
    camerascontrolwidget.cpp \
    rov_data_types/binary_stream.cpp \
    rov_data_types/crc.cpp \
    rov_data_types/rov_data_types.cpp \
    rov_data_types/serializable.cpp \
    ethernet/datastore.cpp \
    ethernet/tcpconnetor.cpp \
    joystick/joystickmanager.cpp \
    joystick/joystickmediator.cpp \
    joystick/joystickconfigdialog.cpp \
    joystick/clickablelabel.cpp \
    video/camerasconfigdialog.cpp \
    video/videosurface.cpp \
    joystick/joystickdebugdialog.cpp \
    ethernet/datadebugdialog.cpp \
    sensorswidget.cpp \
    ethernet/packagedebugdialog.cpp \
    infowidget.cpp

HEADERS += \
    mainwindow.hpp \
    mainwidget.hpp \
    joystick\joystickmanager.hpp \
    video/videowidget.hpp \
    video/usbcamerawidget.hpp \
    timerwidget.hpp \
    video/ethernetcamerawidget.hpp \
    video/videostreamparser.hpp \
    camerascontrolwidget.hpp \
    rov_data_types/binary_stream.hpp \
    rov_data_types/crc.hpp \
    rov_data_types/rov_data_types.hpp \
    rov_data_types/serializable.hpp \
    ethernet/datastore.hpp \
    ethernet/tcpconnetor.hpp \
    joystick/joystickmediator.hpp \
    joystick/joystickconfigdialog.hpp \
    joystick/clickablelabel.hpp \
    video/camerasconfigdialog.hpp \
    video/videosurface.hpp \
    joystick/joystickdebugdialog.hpp \
    ethernet/datadebugdialog.hpp \
    sensorswidget.hpp \
    ethernet/packagedebugdialog.hpp \
    infowidget.hpp
