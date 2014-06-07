#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include "../includes.h"

namespace DataProcess {

class InputData
{
public:
    InputData() {}
    QVector <int> values;
    bool operator == (const InputData &) { return true; }
};

class OutputData
{
public:
    OutputData() {}
    QVector <double> values;
    bool operator == (const OutputData &) { return true; }
};

//-------------------------------------------------------------------------------------------------
struct AbstractProcessor : public QObject {
    virtual ~AbstractProcessor() {}
    virtual InputData * prepareData(QImage &) = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
