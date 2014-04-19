#ifndef NEUNETFACTORY_H
#define NEUNETFACTORY_H

#include <QDataStream>
#include "../NeuNet/AbstractNet.h"

namespace Factory{

// Abstract Factory
class AbstractNetFactory
{
public:
    virtual NeuNets::AbstractNet *createNet(QString filename) = 0;
    virtual void parseFile(QString filename) = 0;

};
} // namespace Factory
#endif // NEUNETFACTORY_H
