#ifndef NNABSTRACTDESTROYER_H
#define NNABSTRACTDESTROYER_H
#include "../NeuNet/AbstractNet.h"

namespace Factory{

using NeuNets::AbstractNet;

class AbstractNetDestroyer
{
public:
    virtual ~AbstractNetDestroyer() {}
    virtual void destroy(NeuNets::AbstractNet *nnet) = 0;
};

} // namespace Factory
#endif // NNABSTRACTDESTROYER_H
