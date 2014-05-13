#include "MultiLayerNet.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {

MultiLayerNet::MultiLayerNet() : sigmoid(FuncDisp::func("Sigmoid")) {
    inLayerNum = 0;
    outLayerNum = 0;
}

MultiLayerNet::MultiLayerNet (const Func &sigma,
                              const NeuVec &inNeuVec,
                              const NeuVec &outNeuVec,
                              const uint _layersCnt)
    :    inNeurons(inNeuVec), outNeurons(outNeuVec), sigmoid(sigma), layersCnt(_layersCnt)
{
    outLayerNum = outNeuVec.size();
    inLayerNum = inNeuVec.size();
}

MultiLayerNet::~MultiLayerNet() {

}

OutputData MultiLayerNet::getResponse(const InputData &imgs) const{
    if(!imgs.isCorrect()) throw NoImage;


    Iterator layerIter = getInLayer();
    int layerSize = layerIter.count();
    for (int i = 0; i < layerSize; i++){
        layerIter[i] = imgs[i];
    }

    Iterator falseEndLayer = getAfterOut();
    for (layerIter = getInLayer(); layerIter != falseEndLayer ;layerIter.nextLayer()){
        for (int i = 0; i < layerIter.count(); i++){
            layerIter[i].summup();
        }
    }

    layerIter = getOutLayer();
    layerSize = layerIter.count();

    OutputData returnVal;
    for (int i = 0; i < layerSize; i++){
            returnVal[i] = layerIter[i].getVal();
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
Iterator MultiLayerNet::getAfterOut() const{
    return (getOutLayer().nextLayer());
}
Iterator MultiLayerNet::getBeforeIn() const{
    return (getInLayer().prevLayer());
}
} //namespace NeuNets

