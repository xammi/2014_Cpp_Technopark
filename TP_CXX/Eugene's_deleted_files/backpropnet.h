#ifndef BACKPROPNET_H
#define BACKPROPNET_H

#include "abstractnet.h"
#include "BuildInfo.h"

namespace Factory{

// Concrete Product
class BackPropNet: public AbstractNet{

public:
    BackPropNet();
    virtual void printName();
};

} // namespace Factory
#endif // BACKPROPNET_H
