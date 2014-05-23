#ifndef TUTEDATA_H
#define TUTEDATA_H

#include "../includes.h"
#include "DataProcess/AbstractProcessor.h"

namespace NetTutors {

using DataProcess::InputData;
using DataProcess::OutputData;

struct InOutData {
    InputData in;
    OutputData out;
};

// Single Image
struct InOutDataSet {
    QVector<InputData *> inputs;
    QVector<OutputData *> outputs;
};

struct TuteData{
    QVector <InOutDataSet> runData;

    long double maxErr;
    long double minErr;
    long int maxIter;
};

struct CompResult {
    QVector<double> comps;
};

} // namespace NetTutors

#endif // TUTEDATA_H
