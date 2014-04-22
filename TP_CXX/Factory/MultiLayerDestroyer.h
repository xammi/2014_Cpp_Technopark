#ifndef NNDESTROYER_H
#define NNDESTROYER_H
#include "AbstractNetDestroyer.h"
#include "../NeuNet/MultiLayerNet.h"
#include "../NeuNet/Iterator.h"

namespace Factory{

class NNDestroyer : public NNAbstractDestroyer
{
public:
    NNDestroyer();
    void destroy(NeuNets::MultiLayerNet *nNet);
    void writeFile(NeuNets::MultiLayerNet *nNet, const QString &filename);
};




//---------------------------------------------------------
struct FileNotFound : public Exception {
    QString toString() { return "Файл не найден"; }
};
struct NetNotFound : public Exception {
    QString toString() { return "Сеть не создана "; }
};
//---------------------------------------------------------

}// namespace Factory
#endif // NNDESTROYER_H
