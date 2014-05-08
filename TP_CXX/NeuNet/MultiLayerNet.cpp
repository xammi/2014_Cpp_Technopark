#include "MultiLayerNet.h"

namespace NeuNets {

MultiLayerNet::MultiLayerNet() {
    inLayerNum = 0;
    outLayerNum = 0;

}

MultiLayerNet::MultiLayerNet (func sigma,
                              const NeuVec &inNeuVec,
                              const NeuVec &outNeuVec)
    : sigmoid(sigma),
      inNeurons(inNeuVec), outNeurons(outNeuVec)
{
    outLayerNum = outNeuVec.size();
    inLayerNum = inNeuVec.size();
}

MultiLayerNet::~MultiLayerNet() {

}

OutputData MultiLayerNet::getResponse(const InputData &imgs) const{
    if(!imgs.isCorrect()) throw NoImage;

    double result = 0;
    double buf = 0;
    OutputData answer;
    Neuron *netNeuron;
    for (int i = 0; i < outLayerNum; i++) {
        netNeuron = outNeurons.at(i);
        buf = netNeuron->summup(&imgs, sigmoid, i);
        if(buf > result) {
            result = buf;
            answer = netNeuron->value;
        }
    }
    return answer;
}

Iterator MultiLayerNet::getInLayer() const{
    Iterator inIter(inNeurons);
    return inIter;
}

Iterator MultiLayerNet::getOutLayer() const{
    Iterator outIter(outNeurons);
    return outIter;
}

} //namespace NeuNets

