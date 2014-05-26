#include "MultiLayerNet.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {

MultiLayerNet::MultiLayerNet() : activationFunc(FuncDisp::func("Sigmoid")) {
    inLayerNum = 0;
    outLayerNum = 0;
}

MultiLayerNet::MultiLayerNet (const Func &sigma,
                              const NeuVec &inNeuVec,
                              const NeuVec &outNeuVec,
                              const uint _layersCnt)
    :    inNeurons(inNeuVec), outNeurons(outNeuVec), activationFunc(sigma), layersCnt(_layersCnt)
{
    outLayerNum = outNeuVec.size();
    inLayerNum = inNeuVec.size();
}

MultiLayerNet::~MultiLayerNet() {}

DataProcess::OutputData MultiLayerNet::getResponse(const DataProcess::InputData &imgs) const {
    Iterator layerIter = getInLayer();
    int layerSize = layerIter.count();

    for (int i = 0; i < layerSize; i++){
        layerIter[i].setVal(imgs.values[i]);
    }

    Iterator falseEndLayer = getAfterOut();

    // Первый слой не изменяем!!!
    layerIter.nextLayer();
    for ( ; layerIter != falseEndLayer ;layerIter.nextLayer()){
        for (int i = 0; i < layerIter.count(); i++){
            layerIter[i].summup(activationFunc);
        }
    }

    layerIter = getOutLayer();
    layerSize = layerIter.count();

    OutputData returnVal;
    returnVal.values.resize(layerSize);
    for (int i = 0; i < layerSize; i++){
            returnVal.values[i] = layerIter[i].getVal();
        }
    return returnVal;

}

Iterator MultiLayerNet::getInLayer() const{

    Iterator inIter(inNeurons);
    return inIter;
}

Iterator MultiLayerNet::getOutLayer() const{
    Iterator outIter(outNeurons);
    return outIter;
}

QString MultiLayerNet::topology() const {
    Iterator inIter = getInLayer();
    Iterator outIter = getAfterOut();

    QString description;

    for(;inIter != outIter; inIter.nextLayer()){

        description += QString::number(inIter.count());
        if (inIter[0].getSynapseCnt(OUT) != 0)
            description += ", ";
    }

    return description;
}

void MultiLayerNet::clear()
{
    Iterator inIter = getBeforeIn();
    Iterator outIter = getAfterOut();

    for(; inIter != outIter; inIter.nextLayer()){
        SynapseAct sAct = [] (Synapse &synapse) {
            synapse.changeWeight(0);
        };
        NeuronAct nAct = [ &sAct ] (Neuron &neuron) {
            neuron.setVal(0);
            neuron.apply(sAct, OUT);
        };
        inIter.apply(nAct);
    }
}

} //namespace NeuNets

