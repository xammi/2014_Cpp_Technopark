#include "Neuron.h"

namespace NeuNets {

Neuron::Neuron() {

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

}//namespace NeuNets
