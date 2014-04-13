#ifndef NNDESTROYER_H
#define NNDESTROYER_H
#include "NnAbstractDestroyer.h"

namespace Factory{

class NNDestroyer : public NNAbstractDestroyer
{
public:
    NNDestroyer();
    void destroy(NeuNets::AbstrNet *nnet);
};

}// namespace Factory
#endif // NNDESTROYER_H
