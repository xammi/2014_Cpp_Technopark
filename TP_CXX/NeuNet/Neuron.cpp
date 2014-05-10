#include "Neuron.h"

namespace NeuNets {

Neuron::Neuron() {

}

void Neuron::setSynapse(Synaps *syn){
    if(syn == 0)
        return;
    if(syn->from == this){
        this->outSyn = syn;
    }
    else if(syn->to == this){
        this->inSyn = syn;
    }
    else{
        ;
    }
}


double Neuron::summup(InputData imgs, const Func &sigmoid){
    double outputValue = 0;
    if(layer == INPUT) {

        //Somehow take information from imgs
    }
    else {
        int prevLayerSize = inSyn.size();
        for(int i = 0; i < prevLayerSize; i++){
            outputValue += inSyn[i]->weight * inSyn[i]->from->summup(imgs, sigmoid);
        }
        outputValue = sigmoid(outputValue);
    }
    return outputValue;
}

void Neuron::changeOutSyn(double *neuWeights){
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
