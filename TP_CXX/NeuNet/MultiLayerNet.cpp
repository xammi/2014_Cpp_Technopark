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

DataProcess::OutputData MultiLayerNet::getResponse(const InputData &imgs) {
    //check correctivity of Image

    double result = 0;
    double buf = 0;
    DataProcess::OutputData localAnswer;
    Neuron *netNeuron;
    for (int i = 0; i < outLayerNum; i++) {
        netNeuron = outNeurons.at(i);
        buf = netNeuron->summup(imgs, sigmoid);
        if(buf > result) {
            result = buf;
            //answer = netNeuron->value;
        }
    }
    return localAnswer;
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
    Iterator outIter = getOutLayer();

    QString description;
//    do {
//        description += QString::number(inIter.count());
//        inIter.nextLayer();
//    } while (inIter != outIter);

    return description;
}

} //namespace NeuNets

