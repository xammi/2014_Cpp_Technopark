#include "Neuron.h"

namespace NeuNets {

Neuron::Neuron() {

}

double Neuron::summup(InputData imgs, func sigmoid){
    double outputValue = 0;
    if(layer == "input") {

        //Somehow take information from imgs
    }
    else {
        int prevLayerSize = inSyn.size();
        for(int i = 0; i < prevLayerSize; i++){
            outputValue += inSyn.at(i).weight * inSyn.at(i).from->summup(imgs, sigmoid);
        }
        outputValue = sigmoid(outputValue);
    }
    return outputValue;
}

int Neuron::changeOutSyn(double *neuWeights){
    int outSynNum = outSyn.size();
    for (int i = 0; i < outSynNum; i++){
        outSyn.at(i).weight = neuWeights[i];
    }
}

}//namespace NeuNets
