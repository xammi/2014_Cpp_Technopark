#ifndef TUTITIONDATA_H
#define TUTITIONDATA_H

#include "../includes.h"
#include "DataProcess/AbstractProcessor.h"

struct TuteData {
    QVector<DataProcess::InputData *> inputs;
    QVector<DataProcess::OutputData *> outputs;
};


struct CompResult {};
#endif // TUTITIONDATA_H
