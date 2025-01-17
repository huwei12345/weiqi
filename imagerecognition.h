#ifndef IMAGERECOGNITION_H
#define IMAGERECOGNITION_H
#include "boardwidget.h"

class imageRecognition
{
public:
    imageRecognition();

    void recogniton(QImage image, std::vector<std::vector<Piece>> boarder);
};

#endif // IMAGERECOGNITION_H
