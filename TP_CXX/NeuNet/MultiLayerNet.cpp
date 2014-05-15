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

MultiLayerNet::~MultiLayerNet() {}

DataProcess::OutputData MultiLayerNet::getResponse(const DataProcess::InputData &imgs) const {
//    if(!imgs.)
//        throw NoImage();


    Iterator layerIter = getInLayer();
    int layerSize = layerIter.count();
    for (int i = 0; i < layerSize; i++){
        layerIter[i].setVal(imgs.values[i]);
    }

    Iterator falseEndLayer = getAfterOut();
    for (layerIter = getInLayer(); layerIter != falseEndLayer ;layerIter.nextLayer()){
        for (int i = 0; i < layerIter.count(); i++){
            layerIter[i].summup(sigmoid);
        }
    }

    layerIter = getOutLayer();
    layerSize = layerIter.count();

    OutputData returnVal;
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
    }

    return description;
}
Iterator MultiLayerNet::getAfterOut() const{
    Iterator bufIter = this->getOutLayer();
    bufIter.nextLayer();
    return (bufIter);
}
Iterator MultiLayerNet::getBeforeIn() const{
    Iterator bufIter = this->getInLayer();
    bufIter.prevLayer();
    return (bufIter);
}

} //namespace NeuNets

