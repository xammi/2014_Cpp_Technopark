#include "BackPropTutor.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------
BackPropTutor::BackPropTutor()
{}

void BackPropTutor::setNet(NeuNets::MultiLayerNet *net){ // TODO: not NULL
    if((!net) && (currentNet))
        throw NetNotFound();
    currentNet = net;
}

void BackPropTutor::setTester(NetManagers::Tester *test){
    if((!test) && (currentTester))
        currentTester = test;
}

bool BackPropTutor::start(const TuteData &Data){
    return true;
}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
