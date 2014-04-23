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


typedef QVector<int *> SynapsWeights;

// Concrete Factory
class MultiLayerFactory: public AbstractNetFactory
{
    struct Layer {
        uint neuroCount;

        QVector <NeuNets::Neuron *> neuron;
        QVector <NeuNets::Synaps *> synaps;
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

    NeuNets::AbstractNet *createFromFile(const QString &filename);
    NeuNets::AbstractNet *createFromInfo(BuildInfo newInfo);
    void parseFile(const QString &filename);
    void writeFile(const QString &filename);

};

//-------------------------------------
struct WrongFileFormat : public Exception {
    QString toString() { return "Неверный формат файла"; }
};

struct FileNotFound : public Exception {
    QString toString() { return "Файл не найден"; }
};
//--------------------------------------

} // namespace Factory
#endif // BACKPROPNETFACTORY_H
