#ifndef TESTER_H
#define TESTER_H

#include "../NeuNet/AbstractNet.h"
#include "../NetTutors/TuteData.h"

#include "../DataProcess/AbstractProcessor.h"

namespace NetManagers {

using NeuNets::AbstractNet;
using namespace DataProcess;

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
    QString test(const InputDataSet &);

    void setTarget(AbstractNet *);

private:
    AbstractNet *target;
    int findMax(const OutputData &out);
};
//-------------------------------------------------------------------------------------------------
struct TargetNotFound : public Exception {
    QString toString() { return "Для tester не задана нейронная сеть"; }
};

struct SizeMismatch : public Exception {
    QString toString() { return "Размеры вектора ошибок и выхода разные"; }
};

struct InputsOutputsMismatch : public Exception {
    QString toString() { return "Количество входных образов должно быть равно количеству выходных"; }
};

struct InputsNeuNetInLayerSizeMismatch : public Exception {
    QString toString() { return "Размеры входного образа не подходят под размеры входного слоя сети"; }
};

struct OutputsNeuNetOutLayerSizeMismatch : public Exception {
    QString toString() { return "Размеры выходного вектора не подходят под размеры выходного слоя сети"; }
};

struct OutputDataIsEmpty : public Exception {
    QString toString() { return "Выходной вектор пуст. Операции невозможны"; }
};

struct NetNotTuted : public Exception {
    QString toString() { return "Выходной вектор пуст. Операции невозможны"; }
};

} // namespace Tester
#endif // TESTER_H
