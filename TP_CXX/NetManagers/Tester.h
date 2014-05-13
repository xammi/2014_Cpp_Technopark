#ifndef TESTER_H
#define TESTER_H

#include "../NeuNet/AbstractNet.h"
#include "../NetTutors/TutitionData.h"

#include "../DataProcess/AbstractProcessor.h"

namespace NetManagers {

using NeuNets::AbstractNet;
using DataProcess::InputData;
using DataProcess::OutputData;

typedef bool CompResult;
//-------------------------------------------------------------------------------------------------
class Tester : public QObject {
    Q_OBJECT

signals:
    void toDebug(QString);

public:
    Tester();
    Tester(AbstractNet *);

    CompResult test(const InputData &, const OutputData &);
    void setTarget(AbstractNet *);

private:
    AbstractNet *target;
};
//-------------------------------------------------------------------------------------------------
} // namespace Tester
#endif // TESTER_H
