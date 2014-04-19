#ifndef BACKPROPTUTOR_H
#define BACKPROPTUTOR_H

#include "AbstractTutor.h"
#include "../NeuNet/MultiLayerNet.h"
#include "../NetManagers/Tester.h"
namespace NetTutors {

//-------------------------------------------------------------------------------------------------
class BackPropTutor : public AbstractTutor {
    Q_OBJECT
public:
    BackPropTutor();
    BackPropTutor(NetManagers::Tester *test): currentTester(test) {}

    void initialize() {}
    bool start(const TuteData &Data);

    void setNet(NeuNets::MultiLayerNet *net);
    void setTester(NetManagers::Tester *test);

private:
    NeuNets::MultiLayerNet *currentNet;
    NetManagers::Tester *currentTester;

    double propagate() {return 0;}
    void backPropagate() {}

};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors
#endif // BACKPROPTUTOR_H
