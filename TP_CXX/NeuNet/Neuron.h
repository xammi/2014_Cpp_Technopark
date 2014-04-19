#ifndef NEURON_H
#define NEURON_H

#include "../includes.h"
#include <functional>

namespace NeuNets{

typedef QVector<double> row;

struct NetImage{
    QVector<row *> *rows;
};

enum neuronPos {input, hidden, output};

typedef char* OutputData;
typedef NetImage InputData;

typedef double (* func)(double);
//typedef std::function <double (double)> ofunc;


struct Synaps;

class Neuron  {
public:
    Neuron();
    double summup(InputData imgs, func sigmoid);
    void setSynapse(Neuron *otherNeu, double weight); //Set weight of synapse between this Neuron and otherNeu

    OutputData value;

    neuronPos getLayer() {return layer;}
    QVector<Synaps *>* getInSyn() {return &inSyn;}
    QVector<Synaps *>* getOutSyn() {return &outSyn;}

private:
    neuronPos layer;
    QVector<Synaps *> inSyn;
    QVector<Synaps *> outSyn;
};

struct Synaps {
    double weight;
    Neuron *to;
    Neuron *from;
};



}//namespace NeuNets
#endif // NEURON_H

