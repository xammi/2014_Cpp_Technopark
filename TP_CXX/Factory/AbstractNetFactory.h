#ifndef NEUNETFACTORY_H
#define NEUNETFACTORY_H

#include <QDataStream>
#include "BuildInfo.h"
#include "../NeuNet/AbstractNet.h"

namespace Factory{

using namespace BuildData;

// Abstract Factory
class AbstractNetFactory
{
public:
//    virtual NeuNets::AbstractNet *createNet(QString filename) = 0;
    virtual NeuNets::AbstractNet *createFromFile(const QString &filename) = 0;
    virtual NeuNets::AbstractNet *createFromInfo(BuildInfo newInfo) = 0;
};
} // namespace Factory
#endif // NEUNETFACTORY_H
