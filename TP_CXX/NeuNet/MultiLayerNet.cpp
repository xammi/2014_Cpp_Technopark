#include "MultiLayerNet.h"

namespace NeuNets {
MultiLayerNet::MultiLayerNet() {
    neuronNum = 0;
    inLayerNum = 0;
    outLayerNum = 0;

}

MultiLayerNet::~MultiLayerNet() {

}

OutputData MultiLayerNet::getResponse(const InputData &imgs) const {
        //check correctivity of Image

        double result = 0;
        double buf = 0;
        OutputData answer;
        Neuron *netNeuron;
        for (int i = 0; i < neuronNum; i++) {
            netNeuron = neurons.at(i);
            if (netNeuron->getLayer() == "output")
                buf = netNeuron->summup(imgs, sigmoid);
            if(buf > result) {
                result = buf;
                answer = netNeuron->value;
            }
        }
        return answer;
    }
MultiLayerNet::MultiLayerNet (uint neuNum,
                              func sigma,
                              NeuVec &inNeuVec,
                              NeuVec &outNeuVec)
    :neuronNum (neuNum), sigmoid(sigma),
      inNeurons(inNeuVec), outNeurons(outNeuVec)
{}

Iterator MultiLayerNet::getInLayer() const{
    Iterator inIter(inNeurons);
    return inIter;
}
Iterator MultiLayerNet::getOutLayer() const{
    Iterator outIter(outNeurons);
    return outIter;
}

} //namespace NeuNets

