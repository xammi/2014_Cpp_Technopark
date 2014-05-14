#ifndef TUTITIONDATA_H
#define TUTITIONDATA_H

#include "../includes.h"
#include "DataProcess/AbstractProcessor.h"

// Single Image
struct PackedData {
    QVector<DataProcess::InputData *> inputs;
    QVector<DataProcess::OutputData *> outputs;
};

struct TuteData{
    QVector <PackedData> ImageData;
    long double minErr;
    long int maxIter;
};


struct CompResult {};
#endif // TUTITIONDATA_H
