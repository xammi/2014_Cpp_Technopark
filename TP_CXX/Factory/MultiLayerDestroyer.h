#ifndef NNDESTROYER_H
#define NNDESTROYER_H
#include "AbstractNetDestroyer.h"
#include "../NeuNet/MultiLayerNet.h"
#include "../NeuNet/Iterator.h"

namespace Factory{

class MultiLayerDestroyer : public AbstractNetDestroyer
{
public:
    MultiLayerDestroyer();
    void destroy(NeuNets::MultiLayerNet *nNet);
    void writeFile(NeuNets::MultiLayerNet *nNet, const QString &filename);

private:
    NeuNets::UnsafeSynapseAct deleteSynapses;
    NeuNets::UnsafeNeuronAct deleteNeurons;

};

//---------------------------------------------------------
struct FileNotFound : public Exception {
    QString toString() { return "Файл не найден"; }
};
struct NetNotFound : public Exception {
    QString toString() { return "Сеть не создана "; }
};

struct NeuronNotFound : public Exception {
    QString toString() { return "Нейрон не существует. А должен!"; }
};
//---------------------------------------------------------


}// namespace Factory
#endif // NNDESTROYER_H
