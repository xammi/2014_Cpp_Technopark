#ifndef NNDESTROYER_H
#define NNDESTROYER_H
#include "AbstractDestroyer.h"
#include "../NeuNet/MultiLayerNet.h"
#include "../NeuNet/Iterator.h"

namespace Factory{

class MultiLayerDestroyer : public AbstractDestroyer
{
public:
    MultiLayerDestroyer();
    void destroy(AbstractNet *nNet);
    void writeNetToFile(AbstractNet *nNet, const QString &filename);

private:
    UnsafeSynapseAct deleteSynapses;
    UnsafeNeuronAct deleteNeurons;

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

struct WrongKindOfNet : public Exception {
    QString toString() { return "Ожидается экземпляр MultiLayerNet"; }
};

//---------------------------------------------------------


}// namespace Factory
#endif // NNDESTROYER_H
