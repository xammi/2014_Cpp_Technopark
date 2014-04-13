#ifndef NEUNETFACTORY_H
#define NEUNETFACTORY_H

#include <QDataStream>
#include "../NeuNet/abstrnet.h"

namespace Factory{

// Abstract Factory
class AbstractNetFactory
{
public:
    virtual NeuNets::AbstrNet *createNet(QDataStream stream) = 0;
    virtual void parseFile(QDataStream stream) = 0;

};
} // namespace Factory
#endif // NEUNETFACTORY_H
