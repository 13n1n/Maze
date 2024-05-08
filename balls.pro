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

unix: LIBS += -L/usr/lib -lGLU /usr/lib/libbox2d.so
#LIBS: -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc

