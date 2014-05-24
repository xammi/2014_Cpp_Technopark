#ifndef BACKPROPTUTOR_H
#define BACKPROPTUTOR_H


#include "AbstractTutor.h"
#include "../NeuNet/MultiLayerNet.h"

namespace NetTutors {

struct TutorBoundaries{

    TutorBoundaries() {}
    TutorBoundaries( double netErr, double layerErr
                   , int netIter, int layerIter
                   , double curSpeed) :
        maxNetErr(netErr), maxLayerErr(layerErr)
      , maxNetIter(netIter), maxLayerIter(layerIter)
      , speed(curSpeed) {}

    double maxNetErr;
    double maxLayerErr;
    int maxNetIter;
    int maxLayerIter;
    double speed;
};

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
    void setLimits();

private:


    //



    //

    // For Max to set in NetProcessor
    TutorBoundaries limits;
    MultiLayerNet *currentNet;
    Tester *currentTester;

    void getMidLayerErrors(OutputData &oldErrors, OutputData &newErrors, Iterator &it);
    void processImage(const InOutDataSet &image);
    void processLayer(Iterator &it, OutputData &error);

    double propagate() {return 0;}
    void backPropagate() {}
    bool isNormalyzed(OutputData &error);

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
