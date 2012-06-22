#ifndef WEBCAMFACEDETECT_H
#define WEBCAMFACEDETECT_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

#ifdef linux
    #define CASCADE_NAME "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml"
#endif

#ifdef  _WIN32
    #define CASCADE_NAME "C:/Program Files/OpenCV/data/haarcascades/haarcascade_frontalface_alt.xml"
#endif

class Webcamfacedetect{
private:
    int m_x;
    int m_y;
    CvMemStorage* m_storage;
    CvHaarClassifierCascade* m_cascade;
    CvCapture *m_camera;
public:
    Webcamfacedetect(CvCapture *cam);
    int getx();
    int gety();
    void refresh();
};

#endif // WEBCAMFACEDETECT_H
