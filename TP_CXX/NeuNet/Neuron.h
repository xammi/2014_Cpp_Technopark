#ifndef NEURON_H
#define NEURON_H

#include "../includes.h"
#include "../DataProcess/InputData.h"
#include "../DataProcess/OutputData.h"
#include <functional>

namespace NeuNets {

using DataProcess::InputData;
using DataProcess::OutputData;


enum neuronPos { INPUT = 0, HIDDEN, OUTPUT };

typedef double (* func)(double);
//typedef std::function <double (double)> ofunc;


struct Synaps;

class Neuron  {
public:
    Neuron();
    double summup(InputData *imgs, func sigmoid, int i) const;
    void setSynaps(Neuron *otherNeu, double weight); //Set weight of synapse between this Neuron and otherNeu

    OutputData value;

    neuronPos getLayer() {return layer;}
    const QVector<Synaps *> &getInSyn() {return inSyn;}
    const QVector<Synaps *> &getOutSyn() {return outSyn;}

    void changeOutSyn(double *);

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

//================================================================
struct  NoImage: public Exception {
    QString toString() { return "Fail to get image for response"; }
};
struct  NoNeuron: public Exception {
    QString toString() { return "Fail to get neuron for set weight"; }
};
struct  FailLink: public Exception {
    QString toString() { return "No link between neurons. Can't put weight"; }
};
struct  NoWeights: public Exception {
    QString toString() { return "Can't get weight array"; }
};


}//namespace NeuNets
#endif // NEURON_H

