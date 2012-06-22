#ifndef GRAPH_H
#define GRAPH_H

#endif // GRAPH_H

#include <iostream>
#include <vector>
#include <math.h>

#include <QApplication>
#include <QDesktopWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>

#include <GL/gl.h>
#include <GL/glu.h>

#include <Box2D/Box2D.h>

#include "genlab.h"
#include "ball.h"
#include "wall.h"

#define TX_WALL 0
#define TX_GROUND 1
#define TX_FINISH 2
#define TX_WAY 3
#define GL_CLAMP_TO_EDGE 0x812F

class graphics: public QGLWidget, public labirint{
private:
    ball b;
    point view;
    int mH, mW;
    float angleX, angleY;
    unsigned char mapmode;
    GLuint textureID[32];


    void __draw(unsigned _x, unsigned _y);
    void __graphics();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *);
public:
    void collisions();
    void genTextures();

    graphics(int width, int height);
    graphics();
};
