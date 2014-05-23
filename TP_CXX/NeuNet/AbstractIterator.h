#ifndef ABSTRITERATOR_H
#define ABSTRITERATOR_H

#include "../includes.h"

namespace NeuNets {

class AbstractIterator
{
public:
    virtual ~AbstractIterator() {}
    virtual void prevLayer() = 0;
    virtual void nextLayer() = 0;
};

} // namespace NeuNets

#endif // ABSTRITERATOR_H
