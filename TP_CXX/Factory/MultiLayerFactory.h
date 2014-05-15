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

private:
    BuildInfo nnInfo;
//    NeuNets::MultiLayerNet *bpNewNet;
    SynapsWeights weights;

    bool currentMode;  // 0 - fromFILE 1 - fromDATA

    NeuNets::MultiLayerNet *allocMemory(NeuNets::MultiLayerNet *bpNewNet);
    void assembly(NeuNets::NeuVec &prevLayer, NeuNets::NeuVec &curLayer, int layerPos);


    void createFromInfoRec(const NCounts &, int, BuildInfo &, QVector<AbstractNet *> &);


public:
    MultiLayerFactory(bool flag = true);
    ~MultiLayerFactory();

    NeuNets::MultiLayerNet *createFromFile(const QString &filename);
    NeuNets::MultiLayerNet *createFromInfo(const BuildInfo &newInfo);

    void createFromInfo(const QString &, const QString &, const NCounts &cnts, QVector<AbstractNet *> &);

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
