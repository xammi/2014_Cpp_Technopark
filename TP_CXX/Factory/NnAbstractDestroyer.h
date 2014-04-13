#ifndef NNABSTRACTDESTROYER_H
#define NNABSTRACTDESTROYER_H
#include "../NeuNet/abstrnet.h"

namespace Factory{

using NeuNets::AbstrNet;

class NNAbstractDestroyer
{
public:
    virtual ~NNAbstractDestroyer() {}
    virtual void destroy(NeuNets::AbstrNet *nnet) = 0;
};

} // namespace Factory
#endif // NNABSTRACTDESTROYER_H
