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

    void prepareImg(InputData &, const QImage &inImg);
    void prepareImgSet(InputDataSet &dataSet, const QImage &inImg);
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
    void bitToImg(QBitArray *segm, QImage *&segmImg);
    void toInputData(QImage &iniImage, InputData &data);


    int getMaxX(QBitArray *segm, int &firstX);
    int getMaxY(QBitArray *segm, int &firstY);
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGEPROCESSOR_H
