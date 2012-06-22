#include "webcamfacedetect.h"

Webcamfacedetect::Webcamfacedetect(CvCapture *cam){
    if(cam != NULL){
        m_storage = cvCreateMemStorage(0);
        m_cascade = (CvHaarClassifierCascade*)cvLoad(CASCADE_NAME, 0, 0, 0);
        m_camera = cam;
        refresh();
    }
}

inline int Webcamfacedetect::getx(){
    return m_x;
}

inline int Webcamfacedetect::gety(){
    return m_y;
}

void Webcamfacedetect::refresh(){
    IplImage *frame = cvQueryFrame(m_camera);
    int diagonal = 0;
    int fsize[] = {frame->width, frame->height};

    cvClearMemStorage(m_storage);
    if(m_cascade){
        CvSeq* faces = cvHaarDetectObjects(frame, m_cascade, m_storage, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(40, 40));
        for(int i = 0; i < (faces ? faces->total : 0); i++){
            CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
            int tx = r->x + r->width/2, ty = r->y + r->height/2;
            if(diagonal < tx*tx + ty*ty){
                diagonal = tx*tx + ty*ty;
                m_x = tx - fsize[0]/2;
                m_y = ty - fsize[1]/2;
            }
        }
    }
}
