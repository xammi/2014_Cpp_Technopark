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
};
//-------------------------------------------------------------------------------------------------
class InputData
{
public:
    InputData() {}
    QVector <double> values;
    bool operator == (const InputData &) { return true; }
};
typedef QVector<InputData *> InputDataSet;

class OutputData
{
public:
    OutputData() {}
    QVector <double> values;
    bool operator == (const OutputData &) { return true; }
};
typedef QVector<OutputData *> OutputDataSet;
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
