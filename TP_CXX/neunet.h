#ifndef NEUNET_H
#define NEUNET_H

namespace NeuNets{

class NeuNet;
class Neuron;
struct Synaps;

typedef QVector<Neuron *> NeuVec;
typedef QVector<Image *> InputData;
typedef char* OutputData ;  //return char at this coding point
                            //may change to type which we want
                            //to return on output layer


class MultiLayerNet {
public:
    NeuNet();
    NeuNet(uint neuNum, uint inNeuNum, uint outNeuNum);
    ~NeuNet();
    int saveToFile(QString fileName);      //save results to file from inside result array
    int loadFromFile(QString fileName);    //load data from file and save results inside
    OutputData getResponse(InputData imgs);
    QVector <Synaps *> getSynaps();         //return all(?) synaps to change their weght during education
                                            //probably better way to return synapses by their level
    int changeSynaps(double *wieghtArr);

private:
    OutputData resultArr;
    int arrResize();
    uint bufSize, realSize;

    NeuVec neurons;
    uint inLayerNum, hidLayerNum,outLayerNum;
};

} //namespace NeuNets
#endif // NEUNET_H



