#ifndef BACKPROPNETFACTORY_H
#define BACKPROPNETFACTORY_H

#include "AbstractNetFactory.h"
#include "../NeuNet/MultiLayerNet.h"

#include "BuildInfo.h"

namespace Factory{

using NeuNets::Neuron;
using NeuNets::Synaps;
using NeuNets::MultiLayerNet;
using NeuNets::AbstractNet;


typedef QVector<double *> SynapsWeights;

// Concrete Factory
class MultiLayerFactory: public AbstractNetFactory
{
    struct Layer {
        uint neuroCount;

        NeuNets::NeuVec neuron;
    };

private:
    BuildInfo nnInfo;
    NeuNets::MultiLayerNet *bpNewNet;
    SynapsWeights weights;

    bool currentMode;  // 0 - fromFILE 1 - fromDATA

    void allocMemory() ;
    void assembly(Layer &prevLayer, Layer &curLayer, int layerPos);


public:
    MultiLayerFactory(bool flag = true);
    ~MultiLayerFactory();

    NeuNets::MultiLayerNet *createFromFile(const QString &filename);
    NeuNets::MultiLayerNet *createFromInfo(BuildInfo newInfo);

    void parseFile(const QString &filename);
    void writeFile(const QString &filename);
};





//-------------------------------------
struct WrongFileFormat : public Exception {
    QString toString() { return "Неверный формат файла"; }
};

struct ReadFileNotFound : public Exception {
    QString toString() { return "Файл для чтения не найден"; }
};

struct WrongData : public Exception {
    QString toString() { return "Неверный формат данных"; }
};
//--------------------------------------

} // namespace Factory
#endif // BACKPROPNETFACTORY_H
