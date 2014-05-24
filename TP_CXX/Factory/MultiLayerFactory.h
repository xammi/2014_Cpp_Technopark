#ifndef BACKPROPNETFACTORY_H
#define BACKPROPNETFACTORY_H

#include "AbstractFactory.h"
#include "../NeuNet/MultiLayerNet.h"

#include "BuildInfo.h"

namespace Factory{

using namespace NeuNets;

typedef QVector<double *> SynapseWeights;

// Concrete Factory
class MultiLayerFactory: public AbstractFactory
{

private:
    BuildInfo nnInfo;
    QString recArea;

//    NeuNets::MultiLayerNet *bpNewNet;
    SynapseWeights weights;

    bool currentMode;  // 0 - fromFILE 1 - fromDATA

    MultiLayerNet *allocMemory(MultiLayerNet *bpNewNet);
    void assembly(NeuVec &prevLayer, NeuVec &curLayer, int layerPos);


    void createFromInfoRec(const NCounts &, int, BuildInfo &, QVector<AbstractNet *> &);


public:
    MultiLayerFactory(bool flag = true);
    ~MultiLayerFactory();

    MultiLayerNet *createFromFile(const QString &filename);
    MultiLayerNet *createFromInfo(const BuildInfo &newInfo);

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
