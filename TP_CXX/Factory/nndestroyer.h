#ifndef NNDESTROYER_H
#define NNDESTROYER_H
#include "nnabstractdestroyer.h"

namespace Factory{

class NNDestroyer : public NNAbstractDestroyer
{
public:
    NNDestroyer();
    void destroy(AbstrNet *nnet);
};

}// namespace Factory
#endif // NNDESTROYER_H
