#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "AbstractProcessor.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
class ImageProcessor : public AbstractProcessor {
    Q_OBJECT

public:
    ImageProcessor();

    void processData(InputData &, const QImage &) {}

private:
    QImage iniImage;
    QVector <QImage *> segments;

    void binarize() {}
    void segment() {}
    void crop() {}
    void resize() {}

};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGEPROCESSOR_H
