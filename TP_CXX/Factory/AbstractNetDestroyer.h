#ifndef NNABSTRACTDESTROYER_H
#define NNABSTRACTDESTROYER_H
#include "../NeuNet/AbstractNet.h"

namespace Factory{

using NeuNets::AbstractNet;

class NNAbstractDestroyer
{
public:
    virtual ~NNAbstractDestroyer() {}
    virtual void destroy(NeuNets::AbstractNet *nnet) = 0;
};

} // namespace Factory
#endif // NNABSTRACTDESTROYER_H
