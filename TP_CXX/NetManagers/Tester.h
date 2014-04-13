#ifndef TESTER_H
#define TESTER_H

#include "../NeuNet/abstrnet.h"
#include "../NetTutors/TutitionData.h"

#include "../DataProcess/InputData.h"
#include "../DataProcess/OutputData.h"

namespace NetManagers {

using NeuNets::AbstrNet;
using DataProcess::InputData;
using DataProcess::OutputData;

typedef bool CompResult;
//-------------------------------------------------------------------------------------------------
class Tester : public QObject {
    Q_OBJECT
public:
    Tester();
    Tester(AbstrNet *);

    CompResult test(const InputData &, const OutputData &);
    void setTarget(AbstrNet *);

private:
    AbstrNet *target;
};
//-------------------------------------------------------------------------------------------------
} // namespace Tester
#endif // TESTER_H
