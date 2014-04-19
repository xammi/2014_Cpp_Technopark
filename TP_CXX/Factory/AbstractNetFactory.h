#ifndef NEUNETFACTORY_H
#define NEUNETFACTORY_H

#include <QDataStream>
#include "../NeuNet/abstrnet.h"

namespace Factory{

// Abstract Factory
class AbstractNetFactory
{
public:
    virtual NeuNets::AbstrNet *createNet(QString filename) = 0;
    virtual void parseFile(QString filename) = 0;

};
} // namespace Factory
#endif // NEUNETFACTORY_H
