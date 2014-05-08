#include "Iterator.h"

namespace NeuNets {
Iterator::Iterator(const NeuVec &NV){
    neuronLayer = NV;
    ptrPos = 0;
}


void Iterator::prevLayer(){
    if(! isCorrect()) throw FailInitializedIter;
    if((neuronLayer[0]).layer == "input")
        throw NoPrevLayer;
    else {
        int curLayerSize = neuronLayer.size();
        Neuron curLayerNeuron = neuronLayer[0];
        int prevLayerSize = (curLayerNeuron.getInSyn())->size() ;

        Synaps pathSynaps;
        for(int i = 0; i < prevLayerSize; i++){
            pathSynaps = (curLayerNeuron.getInSyn())[i];
            neuronLayer.push_front(*pathSynaps.from);
        }

        for(int i = 0; i < curLayerSize; i++){
            neuronLayer.pop_back();
        }
        ptrPos = 0;
    }
}

void Iterator::nextLayer(){
    if(! isCorrect()) throw FailInitializedIter;
    if((neuronLayer[0]).layer == "output") throw NoNextLayer;

    int curLayerSize = neuronLayer.size();
    Neuron curLayerNeuron = neuronLayer[0];
    int nextLayerSize = (curLayerNeuron.getOutSyn())->size() ;
    Synaps pathSynaps;

    for(int i = 0; i < nextLayerSize; i++){
        pathSynaps = (curLayerNeuron.getInSyn())[i];
        neuronLayer.push_front(*pathSynaps.to);
    }

    for(int i = 0; i < curLayerSize; i++){
        neuronLayer.pop_back();
    }
    ptrPos = 0;
}

const Neuron &Iterator::operator[](int i){
    if(isCorrect()){
        ptrPos = i;
        return *neuronLayer[i];
    }
    else
        throw FailInitializedIter;

}

const Neuron &Iterator::nextNeuron(){
    if(isCorrect()){
        ptrPos ++;
        return *neuronLayer[ptrPos];
    }
    else
        throw FailInitializedIter;

}

const Neuron &Iterator::prevNeuron(){
    if(isCorrect()){
        ptrPos --;
        return *neuronLayer[ptrPos];
    }
    else
        throw FailInitializedIter;
}

bool Iterator::isCorrect(){
    return bool(neuronLayer.size());
}
}//namespace NeuNets
