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


//-------------------------------------
struct WrongFileFormat : public Exception {
    QString toString() { return "Неверный формат файла"; }
};

struct FileNotFound : public Exception {
    QString toString() { return "Файл не найден"; }
};
//--------------------------------------

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

    void parseFile(const QString &filename);
    void allocMemory() ;
    void assembly(Layer &prevLayer, Layer &curLayer, int layerPos);

public:

    virtual NeuNets::AbstractNet *createFromFile(const QString &filename);
    virtual NeuNets::AbstractNet *createFromInfo(BuildInfo newInfo);

    void writeFile(const QString &filename);

};

} // namespace Factory
#endif // BACKPROPNETFACTORY_H
