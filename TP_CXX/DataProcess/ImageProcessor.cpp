#include "ImageProcessor.h"


namespace DataProcess {

QRgb black = qRgb(0,0,0);
QRgb white = qRgb(255,255,255);

//-------------------------------------------------------------------------------------------------
ImageProcessor::ImageProcessor():segments(1)
{}


void ImageProcessor::prepareImg(InputData &data, const QImage &inImg) {
    iniImage = inImg;

    xSize = inImg.width();
    ySize = inImg.height();
    imgSize = (xSize*ySize);


    binarize();
    segment();
    toInputData(iniImage, data);
}


void ImageProcessor::prepareImgSet(InputDataSet &dataSet)
{

    dataSet.clear();
    dataSet.resize(segmentsCount);
    for(int  i = 0; i < segmentsCount; i++){
        toInputData(*(segments[i]), *(dataSet[i]));
    }
}

ImageProcessor::~ImageProcessor()
{
    for(int i = 0; i < segments.size(); i++)
        delete segments[i];

}

void ImageProcessor::binarize()
{
    double midVal = 0;
    double koef = 1/double(imgSize);
    for(int x = 0; x < xSize; x++)
        for(int y = 0; y < ySize; y++)
            midVal += qGray(iniImage.pixel(x,y)) * koef;
    ;

    for(int x = 0; x < xSize; x++)
        for(int y = 0; y < ySize; y++)
            if(qGray(iniImage.pixel(x,y)) >= midVal)
                iniImage.setPixel(x, y,  white);
            else
                iniImage.setPixel(x, y , black);
}


void ImageProcessor::startSelectSegment(int x, int y, QBitArray *checkedPixels)
{
    (*checkedPixels)[x + y*xSize] = true;
    selectSegment(x + 1, y, checkedPixels);
    selectSegment(x - 1, y, checkedPixels);
    selectSegment(x, y + 1, checkedPixels);
    selectSegment(x, y - 1, checkedPixels);

}
void ImageProcessor::selectSegment(int x, int y, QBitArray* checkedPixels)
{
    if((iniImage.pixel(x,y)==black) && !(*checkedPixels)[x + y*xSize]){
        (*checkedPixels)[x + y*xSize] = true;
        selectSegment(x + 1, y, checkedPixels);
        selectSegment(x - 1, y, checkedPixels);
        selectSegment(x, y + 1, checkedPixels);
        selectSegment(x, y - 1, checkedPixels);

    }
}

void bitToImg(QBitArray *segm, QImage *segmImg);

void ImageProcessor::segment()
{
    QBitArray checkedPixels(imgSize);
    QBitArray oldPixelArr(imgSize);
    QBitArray segmentBit(imgSize);

    segmentsCount = 0;
    for(int x = 0; x < xSize; x++)
        for(int y = 0; y < ySize; y++){
            if ((iniImage.pixel(x,y)==black) && !checkedPixels[x + xSize*y]){
                startSelectSegment(x,y, &checkedPixels);
                segmentBit = checkedPixels ^ oldPixelArr;
                if(segmentsCount == segments.size())
                    segments.resize(segments.size() * 2);
                bitToImg(&segmentBit, segments[segmentsCount]);
                segmentsCount++;
                oldPixelArr = checkedPixels;
            }
        }
}


void ImageProcessor::bitToImg(QBitArray *segm, QImage *segmImg)
{
    int firstX, firstY;
    int xSegSize =  getMaxX(segm, firstX);
    int ySegSize =  getMaxY(segm, firstY);
    segmImg = new QImage(xSegSize, ySegSize, QImage::Format_RGB32);
    for(int x = firstX; x < firstX + xSegSize; x++)
        for(int y = firstY; y < firstY + ySegSize; y++)
            if((*segm)[x + y*xSize])
                segmImg->setPixel(x - firstX, y - firstY, black);
            else
                segmImg->setPixel(x - firstX, y - firstY, white);
}

int ImageProcessor::getMaxX(QBitArray *segm, int &firstX)
{
    firstX = -1;
    int maxX = 0, xLayer;
    for (int y = 0; y < ySize; y++){
        xLayer = 0;
        for(int x = 0; x < xSize; x++)
            if((*segm)[x + y*xSize]){
                xLayer++;
                if(firstX == -1 || firstX > x){
                    firstX = x;
                }
            }
        if(xLayer > maxX)
            maxX = xLayer;
    }
    return maxX;
}

int ImageProcessor::getMaxY(QBitArray *segm, int &firstY)
{
    firstY = -1;
    int maxY = 0, yLayer;
    for (int x = 0; x < xSize; x++){
        yLayer = 0;
        for(int y = 0; y < ySize; y++)
            if((*segm)[x + y*xSize]){

                yLayer++;
                if(firstY == -1 || firstY > y)
                    firstY = y;
            }
        if(yLayer > maxY)
            maxY = yLayer;
    }
    return maxY;
}

void ImageProcessor::toInputData(QImage &iniImage, InputData &data){
    data.values.clear();
    for(int y = 0; y < ySize; y++)
        for(int x = 0; x < xSize; x++){
            if (iniImage.pixel(x,y) == black)
                data.values << 1;
            else
                data.values << 0;
    }
}

//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
