#ifndef INPUTDATA_H
#define INPUTDATA_H

#include "../includes.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
class InputData
{
public:
    InputData();

    bool operator == (const InputData &) { return true; }
};
//-------------------------------------------------------------------------------------------------
} // namespace InputData
#endif // INPUTDATA_H
