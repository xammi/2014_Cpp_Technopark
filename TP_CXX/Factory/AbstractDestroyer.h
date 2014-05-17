#ifndef NNABSTRACTDESTROYER_H
#define NNABSTRACTDESTROYER_H
#include "../NeuNet/AbstractNet.h"

namespace Factory{

using namespace NeuNets;

class AbstractDestroyer
{
public:
    virtual ~AbstractDestroyer() {}
    virtual void destroy(AbstractNet *) = 0;
    virtual void writeNetToFile(AbstractNet *, const QString &) = 0;
};

} // namespace Factory
#endif // NNABSTRACTDESTROYER_H
