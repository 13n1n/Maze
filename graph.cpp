#ifndef GRAPH_CPP
#define GRAPH_CPP

#endif // GRAPH_CPP

#include "graph.h"

#define SPEED_MULT 0.8f
#define Pi 3.1415
int timer;
float h = 8;
b2World *world;
b2Body* body;

void graphics::__graphics(){
    b = ball(getballroom().getcoords().X + 0.5f,
             getballroom().getcoords().Y + 0.5f, 0.15);
    view = point(b.getcoords().X, b.getcoords().Y);
    angleX = 0;
    angleY = 0;
    mapmode = false;

    timer = startTimer(1000/60);
}


graphics::graphics(){
    __graphics();
}

graphics::graphics(int width, int height): labirint(width, height){
    __graphics();
}

#define K 0.1f

void graphics::timerEvent(QTimerEvent *){
    body->ApplyForce(b2Vec2(b.getforce().X/3.f, b.getforce().Y/3.f), b2Vec2(0.05f, 0.05f));
    world->Step(1.0f / 60.0f, 6, 2);
    if(mapmode){
        view.applysecondnewtonlaw(K);
        view.move(K);
    }
    b.setcoords(body->GetPosition().x, body->GetPosition().y);
    setway(b.getcoords().X, b.getcoords().Y);

    if(getballroom().finish()){
        QMessageBox qmb;
        qmb.setText("level is passed");
        qmb.exec();
        exit(0);
    }

    resizeGL(600, 600);
    updateGL();
}

void graphics::initializeGL(){
    float mat_specular[]={1,1,1,1};
    float pos[4] = {0,0,10,1};
    float dir[3] = {0,0,0};

    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);

    genTextures();
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

    setMouseTracking(true);
    QDesktopWidget *d = QApplication::desktop();
    mW = d->width(); mH = d->height();

    QPoint center(mW/2 - 600/2, mH/2 - 600/2);
    move(center);

    world = new b2World(b2Vec2(0.f, 0.f));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 3.3f; //emulation of air resistanse
    bodyDef.position.Set(b.getcoords().X, b.getcoords().Y);
    body = world->CreateBody(&bodyDef);
    b2MassData mass;
    mass.center = b2Vec2_zero;
    mass.mass = 1;
    mass.I = 0.0125f;
    body->SetMassData(&mass);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 0.0f;
    fixtureDef.restitution = 0.6f;
    fixtureDef.friction = 0.f;
    body->CreateFixture(&fixtureDef);

    for(int i = 0; i < labirint::height; i++){
        for(int j = 0; j < labirint::width; j++){
            room r = getroom(i, j);
            float __x = r.getcoords().X, __y = r.getcoords().Y;
            b2Body *_body;
            if(!r.down()){
                b2BodyDef _bodyDef;
                _bodyDef.type = b2_staticBody;
                _bodyDef.position.Set(__x+0.5f, __y);
                _body = world->CreateBody(&_bodyDef);
                b2PolygonShape _dynamicCircle;
                _dynamicCircle.SetAsBox(0.5f, 0.1f);
                b2FixtureDef _fixtureDef;
                _fixtureDef.shape = &_dynamicCircle;
                _fixtureDef.friction = 0.f;
                _body->CreateFixture(&_fixtureDef);
            }if(!r.left()){
                b2BodyDef _bodyDef;
                _bodyDef.type = b2_staticBody;
                _bodyDef.position.Set(__x, __y+0.5);
                _body = world->CreateBody(&_bodyDef);
                b2PolygonShape _dynamicCircle;
                _dynamicCircle.SetAsBox(0.1f, 0.5f);
                b2FixtureDef _fixtureDef;
                _fixtureDef.shape = &_dynamicCircle;
                _fixtureDef.friction = 0.f;
                _body->CreateFixture(&_fixtureDef);
            }if(!r.up()){
                b2BodyDef _bodyDef;
                _bodyDef.type = b2_staticBody;
                _bodyDef.position.Set(__x+0.5f, __y+1.f);
                _body = world->CreateBody(&_bodyDef);
                b2PolygonShape _dynamicCircle;
                _dynamicCircle.SetAsBox(0.5f, 0.1f);
                b2FixtureDef _fixtureDef;
                _fixtureDef.shape = &_dynamicCircle;
                _fixtureDef.friction = 0.f;
                _body->CreateFixture(&_fixtureDef);
            }if(!r.right()){
                b2BodyDef _bodyDef;
                _bodyDef.type = b2_staticBody;
                _bodyDef.position.Set(__x+1.f, __y+0.5);
                _body = world->CreateBody(&_bodyDef);
                b2PolygonShape _dynamicCircle;
                _dynamicCircle.SetAsBox(0.1f, 0.5f);
                b2FixtureDef _fixtureDef;
                _fixtureDef.shape = &_dynamicCircle;
                _fixtureDef.friction = 0.f;
                _body->CreateFixture(&_fixtureDef);
            }

            _body->SetMassData(&mass);
        }
    }
    QCursor::setPos(mW/2, mH/2);
}

void graphics::genTextures(){
    std::cout << "binding textures\n";
    textureID[TX_WALL] = bindTexture(QPixmap(QString("./textures/wall.jpg")), GL_TEXTURE_2D);

    textureID[TX_GROUND] = bindTexture(QPixmap(QString("./textures/ground.jpg")), GL_TEXTURE_2D);

    textureID[TX_FINISH] = bindTexture(QPixmap(QString("./textures/finish.jpg")), GL_TEXTURE_2D);

    textureID[TX_WAY] = /*textureID[TX_GROUND];/*/bindTexture(QPixmap(QString("./textures/way.jpg")), GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void graphics::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat __x = GLfloat(width)/height;
    glFrustum(-__x, __x, -1.0, 1.0, 2, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float x, y;
    if(mapmode){
        x = view.getcoords().X; y = view.getcoords().Y;
    }else{
        x = b.getcoords().X; y = b.getcoords().Y;
    }

    if(mapmode == 2){
        h = _min(20, h+0.3);
        if(h == 20) mapmode = 3;
    }else if(mapmode == 1){
        h = _max(8, h-0.3);
        if(h == 8){
            mapmode = 0;
            view.setforce(std::pair<float, float> (0, 0));
            view.setpulse(std::pair<float, float> (0, 0));
        }
    }

    gluLookAt(x, y, h,
              x, y, 0,
              0, 1, 0);
    //camera position, camera look-point, vector which normal with "web-cam-line"
}

void graphics::paintGL(){
    //genTextures();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    int k = (mapmode) ? 11 : 6;
    std::pair<unsigned, unsigned> _i(_max((unsigned)b.getcoords().X - k, 0),
                         _min(labirint::width, (unsigned)((mapmode) ? view.getcoords().X : b.getcoords().X) + k)),
                                _j(_max((unsigned)b.getcoords().Y - k, 0),
                          _min(labirint::width, (unsigned)((mapmode) ? view.getcoords().Y : b.getcoords().Y) + k));
    for(unsigned i = _i.first; i < _i.second; i++)
        for(unsigned j = _j.first; j < _j.second; j++){
            try{
                __draw(i, j);
            }catch(char *e){
                printf(e);
            }
        }

    glColor3d(1, 1, 1);
    glTranslated(b.getcoords().X, b.getcoords().Y, b.radius);
    GLUquadricObj *q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    gluSphere(q, b.radius, 50, 50);
    gluDeleteQuadric(q);

    glPopMatrix();
}

inline void __drawall(float x1, float x2, float y1, float y2, float shiftx, float shifty){

    const float sc = 0.5f;
    glBegin(GL_QUAD_STRIP);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(x1, y1, 0);
    glTexCoord2f(0.5f, 0.f);
    glVertex3d(x2, y2, 0);

    glTexCoord2f(0.f, 0.5f);
    glVertex3d(x1, y1, 1);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3d(x2, y2, 1);

    glTexCoord2f(0.f, 0.51f);
    glVertex3d(x1+shiftx, y1+shifty, 1);
    glTexCoord2f(0.5f, 0.51f);
    glVertex3d(x2+shiftx, y2+shifty, 1);

    glTexCoord2f(0.f, 1.f);
    glVertex3d(x1+shiftx, y1+shifty, 0);
    glTexCoord2f(0.5f, 1.f);
    glVertex3d(x2+shiftx, y2+shifty, 0);
    glEnd();

    if(true){
        glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(x1, y2, 0);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(x2 + shiftx, y2, 0);

        glTexCoord2f(0.f, 0.51f);
        glVertex3d(x2 + shiftx, y2, 1);
        glTexCoord2f(0.5f, 0.51f);
        glVertex3d(x1, y2, 1);
        glEnd();
    }

    if(true){
        glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(x1, y1, 0);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(x2 + shiftx, y1, 0);

        glTexCoord2f(0.f, 0.51f);
        glVertex3d(x2 + shiftx, y1, 1);
        glTexCoord2f(0.5f, 0.51f);
        glVertex3d(x1, y1, 1);
        glEnd();
    }

    if(true){
        glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(x2, y1, 0);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(x2, y2 + shifty, 0);

        glTexCoord2f(0.f, 0.51f);
        glVertex3d(x2, y2 + shifty, 1);
        glTexCoord2f(0.5f, 0.51f);
        glVertex3d(x2, y1, 1);
        glEnd();
    }

    if(true){
        glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.5f);
        glVertex3d(x1, y1, 0);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3d(x1, y2 + shifty, 0);

        glTexCoord2f(0.f, 0.51f);
        glVertex3d(x1, y2 + shifty, 1);
        glTexCoord2f(0.5f, 0.51f);
        glVertex3d(x1, y1, 1);
        glEnd();
    }
}

void graphics::__draw(unsigned _x, unsigned _y){
    room r = getroom(_x, _y);
    float x = r.getcoords().X, y = r.getcoords().Y;

    glBindTexture(GL_TEXTURE_2D, textureID[TX_WALL]);
    if(!r.up()){
        __drawall((x) ? x-0.05f : x, (x) ? x+1.05f : x+1.f, y+0.95f, y+0.95f, 0.f, 0.1f);
    }if(!r.right()){
        __drawall(x+0.95f, x+0.95f, y, y+1, 0.1f, 0.f);
    }if(!y && !r.down()){
        __drawall(x, x+1, y, y, 0.f, 0.1f);
    }if(!_x && !r.left()){
        __drawall(x, x, y, y+1, 0.1f, 0.f);
    }float up = !r.up(), rgt = !r.right(), dwn = !r.down(), lft = !r.left();


    if(r.finish()) glBindTexture(GL_TEXTURE_2D, textureID[TX_FINISH]);
    else if(r.way()) glBindTexture(GL_TEXTURE_2D, textureID[TX_WAY]);
    else glBindTexture(GL_TEXTURE_2D, textureID[TX_GROUND]);

    glBegin(GL_QUADS);
    GLfloat light1_diffuse[] = {0.4, 0.7, 0.2};
    GLfloat light1_position[] = {b.getcoords().X, b.getcoords().Y, 0.2, 1.0};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glTexCoord2f(0.f, 0.f);
    glVertex3d(x  +  0.05*lft, y  +  0.05*dwn, 0);
    glTexCoord2f(1, 0.f);
    glVertex3d(x+1 - 0.05*rgt, y  +  0.05*dwn, 0);
    glTexCoord2f(1, 1);
    glVertex3d(x+1 - 0.05*rgt, y+1 - 0.05*up , 0);
    glTexCoord2f(0.f, 1);
    glVertex3d(x  +  0.05*lft, y+1 - 0.05*up , 0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, NULL);
}



void graphics::mouseMoveEvent(QMouseEvent *event){
    float dx = (event->globalX() - mW/2)/(float)(mW/2);
    float dy = (event->globalY() - mH/2)/(float)(mH/2);
}

#define POW 0.005
#define BOUNCE 0.8

void graphics::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    case Qt::Key_Tab:
        mapmode = 2;
        view = b;
        break;
    case Qt::Key_Escape:
        exit(0);
        break;
    case Qt::Key_W:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(0, 1));
        else if(!mapmode)   b.addforce(std::pair<float, float>(0, 1));
        break;
    case Qt::Key_S:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(0, -1));
        else if(!mapmode)   b.addforce(std::pair<float, float>(0, -1));
        break;
    case Qt::Key_D:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(1, 0));
        else if(!mapmode)   b.addforce(std::pair<float, float>(1, 0));
        break;
    case Qt::Key_A:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(-1, 0));
        else if(!mapmode)   b.addforce(std::pair<float, float>(-1, 0));
        break;
    }
}

void graphics::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()){
    case Qt::Key_Tab:
        mapmode = 1;
        break;
    case Qt::Key_Escape:
        exit(0);
        break;
    case Qt::Key_W:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(0, -1));
        else if(!mapmode)   b.addforce(std::pair<float, float>(0, -1));
        break;
    case Qt::Key_S:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(0, 1));
        else if(!mapmode)   b.addforce(std::pair<float, float>(0, 1));
        break;
    case Qt::Key_D:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(-1, 0));
        else if(!mapmode)   b.addforce(std::pair<float, float>(-1, 0));
        break;
    case Qt::Key_A:
        if(mapmode == 3)    view.addforce(std::pair<float, float>(1, 0));
        else if(!mapmode)   b.addforce(std::pair<float, float>(1, 0));
        break;
    }
}
