#ifndef ABSTRNET_H
#define ABSTRNET_H

#include "../includes.h"
#include "Iterator.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {

using DataProcess::InputData;
using DataProcess::OutputData;

class AbstractNet
{
public:
    virtual ~AbstractNet() {}

    virtual Iterator getInLayer() const = 0;
    virtual Iterator getOutLayer() const = 0;

    virtual OutputData getResponse(const InputData &) const = 0;

    virtual QString topology() const = 0;

    Iterator getBeforeIn() const {
        Iterator iter = this->getInLayer();
        iter.prevLayer();
        return iter;
    }
    Iterator getAfterOut() const {
        Iterator iter = this->getOutLayer();
        iter.nextLayer();
        return iter;
    }

    QString name() const { return _name; }
    void setName(const QString &netName) { _name = netName; }

protected:
    QString _name;
};
}//namespace NeuNets {
#endif // ABSTRNET_H
