#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "AbstractProcessor.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
class ImageProcessor : public AbstractProcessor {
    Q_OBJECT

public:
    ImageProcessor();
    InputData PrepareData(int nummer);
private:
    Image iniImage;
    QVector <Image *> segments;

    void binarize() {}
    void segment() {}
    void crop() {}
    void resize() {}

};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGEPROCESSOR_H
