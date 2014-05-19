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

    CompResult test(const InputData &, const OutputData &, OutputData &errors);

    void setTarget(AbstractNet *);

private:
    AbstractNet *target;
};
//-------------------------------------------------------------------------------------------------


struct SizeMismatch : public Exception {
    QString toString() { return "Размеры вектора ошибок и выхода разные"; }
};

} // namespace Tester
#endif // TESTER_H
