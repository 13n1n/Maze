#-------------------------------------------------
#
# Project created by QtCreator 2012-05-06T23:22:39
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = balls
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    graph.cpp \
    genlab.cpp \
    ball.cpp \
    wall.cpp \
    point.cpp

HEADERS  += widget.h \
    graph.h \
    genlab.h \
    ball.h \
    wall.h \
    point.h

FORMS    += widget.ui

unix: LIBS += -L/usr/lib -lGLU
#LIBS: -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -llibBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -llibBox2d
else:unix:!macx:!symbian: LIBS += -L$$PWD/ -llibBox2

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libBox2.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libBox2d.lib
else:unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/liblibBox2.a
