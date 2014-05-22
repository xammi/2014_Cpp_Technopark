#include "Neuron.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {

Neuron::Neuron() {

}


int Neuron::getSynapseCnt(SynapseType stype) const{
    if (stype == IN)
        return inSyn.size();
    return outSyn.size();
}

void Neuron::summup(const Func &function){
    value = 0;
    int prevLayerSize = inSyn.size();
    for (int i = 0; i < prevLayerSize; i++){
        value += inSyn[i]->weight * inSyn[i]->from->value;
    }
    value = function(value);

    /*
    apply([ this ] (Synaps * synaps) {
        value += synaps->weight * synaps->from->value;
    }, IN);
    */
}

void Neuron::setSynapse(Synapse *syn){
    if(syn == 0)
        throw NoNeuron();

    if(syn->from == this){
        this->outSyn.append(syn);
    }
    else if(syn->to == this){
        this->inSyn.append(syn);
    }
    else{
        throw FailLink();
    }
}


void Neuron::changeOutSyn(double *neuWeights){
    if (neuWeights == NULL)
        throw NoWeights();
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
