#ifndef TESTER_H
#define TESTER_H

#include "../NeuNet/AbstractNet.h"
#include "../NetTutors/TuteData.h"

#include "../DataProcess/AbstractProcessor.h"

namespace NetManagers {

using NeuNets::AbstractNet;
using namespace DataProcess;

//struct CompResult {
//    QVector<double> comps;
//};

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
    void test(const InOutDataSet &);

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
