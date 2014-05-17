#ifndef NNABSTRACTDESTROYER_H
#define NNABSTRACTDESTROYER_H
#include "../NeuNet/AbstractNet.h"

namespace Factory{

using NeuNets::AbstractNet;
using namespace NeuNets;

class AbstractNetDestroyer
{
public:
    virtual ~AbstractNetDestroyer() {}
    virtual void destroy(AbstractNet *) = 0;
    virtual void writeNetToFile(AbstractNet *, const QString &) = 0;
};

} // namespace Factory
#endif // NNABSTRACTDESTROYER_H
