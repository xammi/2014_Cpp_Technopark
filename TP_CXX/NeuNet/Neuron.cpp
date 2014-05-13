#include "Neuron.h"
#include "/../AbstractProcessor.h"

namespace NeuNets {

Neuron::Neuron() {

}


void Neuron::summup(const Func &sigmoid) const{
    value = 0;
    int prevLayerSize = inSyn.size();
    for (int i = 0; i < prevLayerSize; i++){
        value += inSyn[i]->weight * inSyn[i]->from->value;
    }
    value = sigmoid(value);

    /*
    apply([ this ] (Synaps * synaps) {
        value += synaps->weight * synaps->from->value;
    }, IN);
    */
}

void Neuron::setSynapse(Synaps *syn){
    if(syn == 0)
        throw NoNeuron;

    if(syn->from == this){
        this->outSyn.append(syn);
    }
    else if(syn->to == this){
        this->inSyn.append(syn);
    }
    else{
        throw FailLink;
    }
}


void Neuron::setSynaps(Neuron *otherNeu, double weight)
{
    if(otherNeu == NULL) throw NoNeuron;
    Synaps *needToChangeWeight = NULL;
    int numNeuronInLayer = inSyn->size();
    for (int i = 0; i < numNeuronInLayer; i++){
        if (inSyn[i]->from == otherNeu)
            needToChangeWeight = &(inSyn[i]);
    }
    numNeuronInLayer = outSyn->size();
    for (int i = 0; i < numNeuronInLayer; i++){
        if (outSyn[i]->to == otherNeu)
            needToChangeWeight = &(outSyn[i]);
    }
    if(needToChangeWeight != NULL)
        needToChangeWeight.weight = weight;
    else throw FailLink;
}

void Neuron::changeOutSyn(double *neuWeights){
    if (nueWeights == NULL) throw NoWeights;
    int outSynNum = outSyn.size();
    for (int i = 0; i < outSynNum; i++){
        outSyn[i]->weight = neuWeights[i];
    }
}

//-------------------------------------------------------------------------------------------------
void Neuron::apply(SynapseAct action, const SynapseType type){
    if (type ==IN || type == IN_OUT)
        for (int I = 0; I < inSyn.size(); ++I)
            action(* inSyn[I]);

    if (type == OUT || type == IN_OUT)
        for (int I = 0; I < outSyn.size(); ++I)
            action(* outSyn[I]);
}

void Neuron::apply(UnsafeSynapseAct action, const SynapseType type) {
    if (type ==IN || type == IN_OUT)
        for (int I = 0; I < inSyn.size(); ++I)
            action(inSyn[I]);

    if (type == OUT || type == IN_OUT)
        for (int I = 0; I < outSyn.size(); ++I)
            action(outSyn[I]);
}


}//namespace NeuNets
