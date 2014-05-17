#include "Iterator.h"

namespace NeuNets {
Iterator::Iterator(const NeuVec &NV){
    zeroFlags();
    neuronLayer = NV;
    ptrPos = 0;
}

void Iterator::prevLayer(){
    if (flagPseudoEnd || flagPseudoBegin || count() == 0){
        flagPseudoEnd = false;
        return;
    }

    if(neuronLayer[0]->getSynapseCnt(IN) == 0){
        flagPseudoBegin = true;
        return;
    }

    SynapseAct action = [ this ] (Synaps &synapse) {
        neuronLayer.push_back(synapse.from);
    };

    Neuron *curNeuron = neuronLayer[0];
    neuronLayer.clear();
    curNeuron->apply(action, IN);

    ptrPos = 0;
}

void Iterator::nextLayer(){
    if (flagPseudoBegin || flagPseudoEnd || count() == 0){
        flagPseudoBegin = false;
        return;
    }

    if(neuronLayer[0]->getSynapseCnt(OUT) == 0){
        flagPseudoEnd = true;
        return;
    }

    SynapseAct action = [ this ] (Synaps &synapse) {
        neuronLayer.push_back(synapse.to);
    };

    Neuron *curNeuron = neuronLayer[0];
    neuronLayer.clear();
    curNeuron->apply(action, OUT);

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

    if(ptrPos >= neuronLayer.size())
        throw PosOutOfRange();
    else{
        ptrPos ++;
        return *neuronLayer[ptrPos];
    }

}

const Neuron &Iterator::prevNeuron() {
    if(flagPseudoEnd)
        throw NoNextLayer();
    if(flagPseudoBegin)
        throw NoPrevLayer();


    if(ptrPos < 0)
        throw PosOutOfRange();
    else{
        ptrPos --;
        return *neuronLayer[ptrPos];
    }
}

bool Iterator::operator ==(const Iterator &rhs) const
{
    return (flagPseudoEnd == rhs.flagPseudoEnd &&
            flagPseudoBegin == rhs.flagPseudoBegin &&
            neuronLayer == rhs.neuronLayer);
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
