#ifndef NNABSTRACTDESTROYER_H
#define NNABSTRACTDESTROYER_H
#include "abstractnet.h"

namespace Factory{

class NNAbstractDestroyer
{
public:
    virtual ~NNAbstractDestroyer() {}
    virtual void destroy(AbstractNet *nnet) = 0;
};

} // namespace Factory
#endif // NNABSTRACTDESTROYER_H
