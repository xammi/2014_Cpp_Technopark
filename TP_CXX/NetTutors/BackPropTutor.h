    #ifndef BACKPROPTUTOR_H
#define BACKPROPTUTOR_H





/*

  Небольшая проблема.
  Поскольку Tutor работает с конкретной сетью, при создании его в NetProcessor'е происходит ошибка
  Там хранятся только Абстрактные сети.
  Если делать Тутор рассчитанным на абстрактные сети, то пропадает возможность некоторых методов (getInLayer, getOutLayer)
  Просьба разобраться с этим как можно скорее.
 */









#include "AbstractTutor.h"
#include "../NeuNet/MultiLayerNet.h"
#include "../NetManagers/Tester.h"
namespace NetTutors {

//-------------------------------------------------------------------------------------------------
class BackPropTutor : public AbstractTutor {
    Q_OBJECT

signals:
    void toDebug(QString);

public:
    BackPropTutor();
    BackPropTutor(NetManagers::Tester *test): currentTester(test) {}

    void initialize() {}
    bool start(const TuteData &data);


    void setNet(NeuNets::AbstractNet *aNet);
    void setTester(NetManagers::Tester *test);

private:
    // For MAX to set int NetProcessor
    double maxError;
    NeuNets::MultiLayerNet *currentNet;
    NetManagers::Tester *currentTester;

    void getMidLayerErrors(DataProcess::OutputData &oldErrors, DataProcess::OutputData &newErrors, NeuNets::Iterator &it);
    void processImage(const PackedData &image);
    void processLayer(NeuNets::Iterator &it, DataProcess::OutputData &error);
    double propagate() {return 0;}
    void backPropagate() {}
    bool isNormalyzed(DataProcess::OutputData &error);

};
//-------------------------------------------------------------------------------------------------

struct InputsOutputsCountMismatch : public Exception {
    QString toString() { return "Количество входов для символа не равно количеству выходов"; }
};

struct NetResponseErrorsCountMismatch : public Exception {
    QString toString() { return "Количество входов для символа не равно количеству выходов"; }
};

struct NetNotFound : public Exception {
    QString toString() { return "Сеть не задана"; }
};

struct TesterNotFound : public Exception {
    QString toString() { return "Не найден тестер"; }
};

struct WrongKindOfNet : public Exception {
    QString toString() { return "Сеть недопустимого типа"; }
};

} // namespace NetTutors
#endif // BACKPROPTUTOR_H
