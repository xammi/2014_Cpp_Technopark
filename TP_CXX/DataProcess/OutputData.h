#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include "../includes.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
class OutputData
{
public:
    OutputData();
    QVector <int> values;
    bool operator == (const OutputData &) { return true; }
};
//-------------------------------------------------------------------------------------------------
} // namespace InputData
#endif // OUTPUTDATA_H
