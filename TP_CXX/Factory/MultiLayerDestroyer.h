#ifndef NNDESTROYER_H
#define NNDESTROYER_H
#include "AbstractNetDestroyer.h"

namespace Factory{

class NNDestroyer : public NNAbstractDestroyer
{
public:
    NNDestroyer();
    void destroy(NeuNets::AbstractNet *nNet);
    void writeFile(NeuNets::AbstractNet *nNet, const QString &filename);
};

}// namespace Factory
#endif // NNDESTROYER_H
