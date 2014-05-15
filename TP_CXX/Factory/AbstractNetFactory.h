#ifndef NEUNETFACTORY_H
#define NEUNETFACTORY_H

#include <QDataStream>
#include "BuildInfo.h"
#include "../NeuNet/AbstractNet.h"

namespace Factory{

using namespace BuildData;
using NeuNets::AbstractNet;

// Abstract Factory
class AbstractNetFactory
{
public:
    virtual ~AbstractNetFactory() {}

    //    virtual NeuNets::AbstractNet *createNet(QString filename) = 0;
    virtual AbstractNet *createFromFile(const QString &filename) = 0;
    virtual AbstractNet *createFromInfo(const BuildInfo &newInfo) = 0;
    virtual void createFromInfo(const QString &, const QString &, const NCounts &, QVector<AbstractNet *> &) = 0;
};
} // namespace Factory
#endif // NEUNETFACTORY_H
