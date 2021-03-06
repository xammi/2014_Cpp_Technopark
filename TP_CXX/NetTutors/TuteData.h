#ifndef TUTEDATA_H
#define TUTEDATA_H

#include "../includes.h"
#include "DataProcess/AbstractProcessor.h"

namespace NetTutors {

using namespace DataProcess;

struct TuteBoundaries{

    TuteBoundaries() {}
    TuteBoundaries( double netErr, double layerErr
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

struct TuteData{
    QList<InputDataSet> inputs;
    QList <OutputDataSet> outputs;
};

template <int X = 0>
void clearTuteData(TuteData &ttdata) {
    for (InputDataSet & set : ttdata.inputs)
        deleteAll(set);

    for (OutputDataSet & set : ttdata.outputs)
        deleteAll(set);
}

} // namespace NetTutors

#endif // TUTEDATA_H
