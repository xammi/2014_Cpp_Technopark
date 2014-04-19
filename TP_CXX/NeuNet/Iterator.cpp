#include "Iterator.h"

namespace NeuNets {
Iterator::Iterator(const NeuVec &NV){
    neuronLayer = NV;
    ptrPos = 0;
}


void Iterator::prevLayer(){
/*    if(isCorrect()){
        //check existance of previous layer
        if((neuronLayer[0]).layer == "input")
            throw("No previous layer");
        else {
            int curLayerSize = neuronLayer.size();
            Neuron curLayerNeuron = neuronLayer[0];
            int prevLayerSize = (curLayerNeuron.getInSyn())->size() ;

            Synaps pathSynaps;
            for(int i = 0; i < prevLayerSize; i++){
                pathSynaps = curLayerNeuron.getInSyn()->at(i);
                neuronLayer.push_front(*pathSynaps.from);
            }

            for(int i = 0; i < curLayerSize; i++){
                neuronLayer.pop_back();
            }
            ptrPos = 0;
        }
    }
    else {
        throw("Iterator not initializated");
    }

*/
}

void Iterator::nextLayer(){
  /*  if(isCorrect()){
        //check existance of previous layer
        if((neuronLayer.at(0)).layer == "output")
            throw("No next layer");
        else {
            int curLayerSize = neuronLayer.size();
            Neuron curLayerNeuron = neuronLayer.at(0);
            int nextLayerSize = (curLayerNeuron.getOutSyn())->size() ;
            Synaps pathSynaps;

            for(int i = 0; i < nextLayerSize; i++){
                pathSynaps = curLayerNeuron.getInSyn()->at(i);
                neuronLayer.push_front(*pathSynaps.to);
            }

            for(int i = 0; i < curLayerSize; i++){
                neuronLayer.pop_back();
            }
            ptrPos = 0;
        }
    }
    else {
        throw("Iterator not initializated");
    }*/
}

const Neuron &Iterator::operator[](int i){
    if(isCorrect()){
        ptrPos = i;
        return *neuronLayer[i];
    }
    else
        throw ("Iterator not initialized");

}

const Neuron &Iterator::nextNeuron(){
    if(isCorrect()){
        ptrPos ++;
        return *neuronLayer[ptrPos];
    }
    else
        throw("Iterator not initialized");

}

const Neuron &Iterator::prevNeuron(){
    if(isCorrect()){
        ptrPos --;
        return *neuronLayer[ptrPos];
    }
    else
        throw ("Iterator not initialized");
}

bool Iterator::isCorrect(){
    return bool(neuronLayer.size());
}
}//namespace NeuNets
