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

struct TutorBoundaries{

    TutorBoundaries() {}
    TutorBoundaries( double netErr, double layerErr
                   , int netIter, int layerIter
                   , double curSpeed) :
        maxNetErr(netErr), maxLayerErr(layerErr)
      , maxNetIter(netIter), maxLayerIter(layerIter)
      , speed(curSpeed) {}

    double maxNetErr;
    double maxLayerErr;
    int maxNetIter;
    int maxLayerIter;
    double speed;
};

// Single Image
struct InOutDataSet {
    QVector<InputData *> inputs;
    QVector<OutputData *> outputs;
};

typedef QVector <InOutDataSet> TuteData;

struct CompResult {
    QVector<double> comps;
};

} // namespace NetTutors

#endif // TUTEDATA_H
