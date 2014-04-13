#ifndef ABSTRNET_H
#define ABSTRNET_H

#include "../includes.h"
#include "../DataProcess/InputData.h"
#include "../DataProcess/OutputData.h"

namespace NeuNets {

using DataProcess::InputData;
using DataProcess::OutputData;

//-------------------------------------------------------------------------------------------------
struct AbstrNet {
    virtual OutputData getResponse(const InputData &) const = 0;
};
}//namespace NeuNets {
#endif // ABSTRNET_H
