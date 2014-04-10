#ifndef NEUNETFACTORY_H
#define NEUNETFACTORY_H


#include "abstractnet.h"

namespace Factory{

// Abstract Factory
class AbstractNetFactory
{
public:
    virtual AbstractNet *createNet(FILE *file) = 0;
    virtual void parseFile(FILE *file) {
        return 0;
    }

};
} // namespace Factory
#endif // NEUNETFACTORY_H
