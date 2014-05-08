#include "Neuron.h"


namespace NeuNets {

Neuron::Neuron() {

}

double Neuron::summup(InputData *imgs, func sigmoid, int i) const{
    if (imgs == NULL) throw NoImage;
        double outputValue = 0;
        if(layer == INPUT) {
            return imgs->getAt(i);
        }
        else {
            int prevLayerSize = inSyn.size();
            for(int i = 0; i < prevLayerSize; i++){
                outputValue += inSyn[i]->weight * inSyn[i]->from->summup(imgs, sigmoid, i);
            }
            outputValue = sigmoid(outputValue);
        }
        return outputValue;

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



}//namespace NeuNets
