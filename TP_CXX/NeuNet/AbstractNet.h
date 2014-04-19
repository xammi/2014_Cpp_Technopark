#ifndef ABSTRNET_H
#define ABSTRNET_H

#include "../includes.h"
#include "Neuron.h"

namespace NeuNets {

typedef QVector<Neuron *> NeuVec;
//typedef QVector<Image *> InputData;
//typedef char* OutputData ;  //return char at this coding point
                            //may change to type which we want
                            //to return on output layer

class AbstractNet
{
public:
    virtual OutputData getResponse() = 0;

};
}//namespace NeuNets {
#endif // ABSTRNET_H
