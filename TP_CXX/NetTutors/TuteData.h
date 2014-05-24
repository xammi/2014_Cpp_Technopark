#ifndef TUTEDATA_H
#define TUTEDATA_H

#include "../includes.h"
#include "DataProcess/AbstractProcessor.h"

namespace NetTutors {

using namespace DataProcess;

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

typedef QVector <InOutDataSet> TuteData;

} // namespace NetTutors

#endif // TUTEDATA_H
