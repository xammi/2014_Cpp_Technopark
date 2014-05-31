#ifndef BACKPROPTUTOR_H
#define BACKPROPTUTOR_H


#include "AbstractTutor.h"
#include "../NeuNet/MultiLayerNet.h"

namespace NetTutors {

using namespace NeuNets;

//-------------------------------------------------------------------------------------------------
class BackPropTutor : public AbstractTutor {
    Q_OBJECT

signals:
    void toDebug(QString);

public:
    BackPropTutor() : currentNet(0), currentTester(0) {}
    BackPropTutor(Tester *test): currentNet(0), currentTester(test) {}


    void initialize() {}
    bool start(const TuteData &data);

    void setNet(AbstractNet *aNet);
    void setTester(Tester *test);
    void setLimits(const TuteBoundaries &limits);

private:

    TuteBoundaries tuteLimits;
    MultiLayerNet *currentNet;
    Tester *currentTester;
    QList<OutputData> everyImageErrors;

    void getMidLayerErrors(OutputData &oldErrors, OutputData &newErrors, Iterator &it);
    void processImage(const InputDataSet &input, const OutputDataSet &output);
    void processLayer(Iterator &it, OutputData &error);

    bool checkEveryImageError();
    void addEveryImageError(OutputData &newError);
    double propagate() {return 0;}
    void backPropagate() {}
    bool isNormalyzed(OutputData &error);
};
//-------------------------------------------------------------------------------------------------

struct InputsOutputsCountMismatch : public Exception {
    QString toString() { return "Количество входных начертаний для символа не равно количеству выходных"; }
};

struct InputOutputNeuNetCountMismatch : public Exception {
    QString toString() { return "Кол-во входов символа не равно кол-ву входов сети и/или кол-во выходов не равно кол-ву выходов сети"; }
};

struct NetResponseErrorsCountMismatch : public Exception {
    QString toString() { return "Размер ответа сети не совпадает с размером ожидаемого вектора ошибок"; }
};

struct NetNotFound : public Exception {
    QString toString() { return "Сеть не задана на этапе Tutor"; }
};

struct TesterNotFound : public Exception {
    QString toString() { return "Не найден тестер на этапе Tutor"; }
};

struct WrongKindOfNet : public Exception {
    QString toString() { return "Сеть недопустимого типа на этапе Tutor"; }
};

} // namespace NetTutors
#endif // BACKPROPTUTOR_H
