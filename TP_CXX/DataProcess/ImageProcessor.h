#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "AbstractProcessor.h"
#include <QBitArray>
#include <QImage>

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
class ImageProcessor : public AbstractProcessor {
    Q_OBJECT

public:
    ImageProcessor();

    InputData * prepareData(QImage &inImg);
    int getSegm() {return segmentsCount;}
    ~ImageProcessor();

private:
    QImage iniImage;
    int imgSize;
    QVector <QImage *> segments;

    int segmentsCount;
    int xSize;
    int ySize;

    void binarize();
    void segment();
    void crop();
    void resize();

    void startSelectSegment(int , int , QBitArray*);
    void selectSegment(int, int, QBitArray*);
    void bitToImg(QBitArray *segm, QImage *segmImg);

    int getMaxX(QBitArray *segm);
    int getMaxY(QBitArray *segm);
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGEPROCESSOR_H
