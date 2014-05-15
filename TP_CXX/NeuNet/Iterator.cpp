#include "Iterator.h"

namespace NeuNets {
Iterator::Iterator(const NeuVec &NV){
    zeroFlags();
    neuronLayer = NV;
    ptrPos = 0;
}


void Iterator::prevLayer(){


    if (flagPseudoEnd){
        flagPseudoEnd = false;
        return;
    }

    if (flagPseudoBegin) return;
    if((neuronLayer[0])->getLayer() == INPUT){
        flagPseudoBegin = true;
        return;
    }

    int curLayerSize = neuronLayer.size();
    Neuron curLayerNeuron = *neuronLayer[0];
    int prevLayerSize = (curLayerNeuron.getInSyn()).size() ;

    Synaps pathSynaps;
    for(int i = 0; i < prevLayerSize; i++){
        pathSynaps = *(curLayerNeuron.getInSyn())[i];
        neuronLayer.push_front(pathSynaps.from);
    }

    for(int i = 0; i < curLayerSize; i++){
        neuronLayer.pop_back();
    }
    ptrPos = 0;

}

void Iterator::nextLayer(){


    if (flagPseudoBegin){
        flagPseudoBegin = false;
        return;
    }

    if (flagPseudoEnd) return;
    if((neuronLayer[0])->getLayer() == OUTPUT){
        flagPseudoEnd = true;
        return;
    }

    int curLayerSize = neuronLayer.size();
    Neuron curLayerNeuron = *neuronLayer[0];
    int nextLayerSize = (curLayerNeuron.getOutSyn()).size() ;
    Synaps pathSynaps;

    for(int i = 0; i < nextLayerSize; i++){
        pathSynaps = *(curLayerNeuron.getOutSyn())[i];
        neuronLayer.push_front(pathSynaps.to);
    }

    for(int i = 0; i < curLayerSize; i++){
        neuronLayer.pop_back();
    }
    ptrPos = 0;
}

const Neuron &Iterator::operator [](int i) const {
    if(flagPseudoEnd)
        throw NoNextLayer();
    if(flagPseudoBegin)
        throw NoPrevLayer();

        return *neuronLayer[i];
}

Neuron &Iterator::operator[](int i){
    if(flagPseudoEnd)
        throw NoNextLayer();
    if(flagPseudoBegin)
        throw NoPrevLayer();


        ptrPos = i;
        return *neuronLayer[i];

}

const Neuron &Iterator::nextNeuron() {
    if(flagPseudoEnd)
        throw NoNextLayer();
    if(flagPseudoBegin)
        throw NoPrevLayer();


        ptrPos ++;
        return *neuronLayer[ptrPos];


}

const Neuron &Iterator::prevNeuron() {
    if(flagPseudoEnd)
        throw NoNextLayer();
    if(flagPseudoBegin)
        throw NoPrevLayer();


        ptrPos --;
        return *neuronLayer[ptrPos];

}

//-------------------------------------------------------------------------------------------------
void Iterator::apply(NeuronAct action) {
    for (int I = 0; I < neuronLayer.size(); ++I)
        action(* neuronLayer[I]);
}

void Iterator::apply(UnmodNeuronAct action) {
    for (int I = 0; I < neuronLayer.size(); ++I)
        action(* neuronLayer[I]);
}

void Iterator::apply(UnsafeNeuronAct action) {
    for (int I = 0; I < neuronLayer.size(); ++I)
        action(neuronLayer[I]);
}

}//namespace NeuNets
