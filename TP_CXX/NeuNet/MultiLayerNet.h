#ifndef NEUNET_H
#define NEUNET_H

#include "abstrnet.h"
#include "neuron.h"

namespace NeuNets{

typedef QVector<Neuron *> NeuVec;
//-------------------------------------------------------------------------------------------------
class MultiLayerNet : public AbstrNet {
public:
    MultiLayerNet();
    MultiLayerNet(uint neuNum, uint inNeuNum, uint outNeuNum);
    ~MultiLayerNet();

    int saveToFile(QString fileName);      //save results to file from inside result array
    int loadFromFile(QString fileName);    //load data from file and save results inside
    OutputData getResponse(const InputData &) const;
    QVector <Synaps *> getSynaps();         //return all(?) synaps to change their weght during education
                                            //probably better way to return synapses by their level
    int initSynaps(double *wieghtArr);
private:
    OutputData resultArr;
    int arrResize();
    uint bufSize, realSize;

    NeuVec neurons;
    uint inLayerNum, hidLayerNum,outLayerNum;
};

} //namespace NeuNets
#endif // NEUNET_H



