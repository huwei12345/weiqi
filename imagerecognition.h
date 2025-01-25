#ifndef IMAGERECOGNITION_H
#define IMAGERECOGNITION_H
#include "piece.h"
#include <QImage>
class ImageRecognition
{
public:
    ImageRecognition();

    void recogniton(QImage image, std::vector<std::vector<Piece> > &boarder);//error
    void recogniton2(QImage image, std::vector<std::vector<Piece> > &boarder);//yes，但是棋盘必须正好
    int recogniton3(QImage image, std::vector<std::vector<Piece> > &boarder);//error
    int recogniton4(QImage image, std::vector<std::vector<Piece> > &boarder);//no
};

#endif // IMAGERECOGNITION_H
