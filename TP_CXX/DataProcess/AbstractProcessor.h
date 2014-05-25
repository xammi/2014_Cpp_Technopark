#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include "../includes.h"

namespace DataProcess {

class InputData;
class OutputData;

//-------------------------------------------------------------------------------------------------
struct AbstractProcessor : public QObject {
    virtual ~AbstractProcessor() {}
    virtual InputData * prepareData(QImage &) = 0;
    void prepareData(QList<QImage> &) {

    }
};
//-------------------------------------------------------------------------------------------------
class InputData
{
public:
    InputData() {}

    //
    InputData(QString &textData) {
        this->values.resize(textData.length());
        for(int i = 0; i < textData.length(); ++i) {
            this->values[i] = 1.0 * (int)(textData[i].toLatin1());
        }
    }

    QVector <double> values;
    bool operator == (const InputData &) { return true; }
};
typedef QVector<InputData *> InputDataSet;

class OutputData
{
public:
    OutputData() {}
    OutputData(int size) { values.resize(size); }
    QVector <double> values;

    void swapVecs(OutputData &from) {
        this->values.clear();
        this->values.resize(from.values.size());
        this->values = from.values;
    }

    void clearAndFill() { this->values.resize(1); this->values.fill(1); }

    bool operator == (const OutputData &) { return true; }
};
typedef QVector<OutputData *> OutputDataSet;

//-------------------------------------------------------------------------------------------------
struct InOutData {
    InputData in;
    OutputData out;
};

struct InOutDataSet {
    QVector<InputData *> inputs;
    QVector<OutputData *> outputs;
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
