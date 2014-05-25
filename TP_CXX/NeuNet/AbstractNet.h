#ifndef ABSTRNET_H
#define ABSTRNET_H

#include "../includes.h"
#include "Iterator.h"
#include "../DataProcess/AbstractProcessor.h"

namespace NeuNets {


//----------------------------------------------
struct  CharIsNotInRecArea: public Exception {
    QString toString() { return "Recognition area doesn't suit this neuron net. Please, create a new NN"; }
};
//----------------------------------------------
using DataProcess::InputData;
using DataProcess::OutputData;
using DataProcess::OutputDataSet;

class AbstractNet
{
public:
    virtual ~AbstractNet() {}

    virtual Iterator getInLayer() const = 0;
    virtual Iterator getOutLayer() const = 0;

    virtual int getInSize() = 0;
    virtual int getOutSize() = 0;

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

    virtual void clear() = 0;

    QString name() const { return _name; }
    void setName(const QString &netName) { _name = netName; }

    const QString &getRecArea() const { return recArea; }
    virtual void setRecArea(const QString &value) = 0;

    void getDataFromSymbol(OutputData & data, int pos, int length) {
        data.values.fill(0, length);
        data.values[pos] = 1;
    }

    void getOutDataSet(OutputDataSet & outVec, QString strToParse){
        outVec.clear();
        int len = strToParse.length();
        OutputData *bufData;

        for(QChar ch : strToParse){
            bufData = new OutputData();
            int pos = recArea.indexOf(ch);

            if(pos == -1)
                throw CharIsNotInRecArea();

            getDataFromSymbol(*bufData, pos, len);
            outVec.append(bufData);
        }
    }

protected:
    QString _name;
    QString recArea; // empty = &
};



}//namespace NeuNets {
#endif // ABSTRNET_H
