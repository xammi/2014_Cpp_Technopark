#ifndef BACKPROPTUTOR_H
#define BACKPROPTUTOR_H

#include "AbstractTutor.h"
#include "../NeuNet/MultiLayerNet.h"
#include "../NetManagers/Tester.h"
namespace NetTutors {

//-------------------------------------
struct NetNotFound : public Exception {
    QString toString() { return "Сеть не задана"; }
};

struct TesterNotFound : public Exception {
    QString toString() { return "Не найден тестер"; }
};
//--------------------------------------

// ошибка одного слоя НС
typedef DataProcess::OutputData CurLayerErr;
// Вектор ошибок для одного образа
typedef QVector < CurLayerErr > CurImageErr;
// Ошибки всей сети
typedef QVector < CurImageErr > TotalErr;



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


    void setNet(NeuNets::MultiLayerNet *net);
    void setTester(NetManagers::Tester *test);

private:
    NeuNets::MultiLayerNet *currentNet;
    NetManagers::Tester *currentTester;

    double propagate() {return 0;}
    void backPropagate() {}
    bool isMinError(DataProcess::OutputData *currentErrors, long double err);
    void changeWeights(NeuNets::Neuron neuron, double error);
    CurLayerErr getMidError(CurLayerErr *curErr, NeuNets::Iterator cur, NeuNets::Iterator prev);

};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors
#endif // BACKPROPTUTOR_H
