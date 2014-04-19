#include "BackPropTutor.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------
BackPropTutor::BackPropTutor()
{}

void BackPropTutor::setNet(NeuNets::MultiLayerNet *net){ // TODO: not NULL
    currentNet = net;
}

void BackPropTutor::setTester(NetManagers::Tester *test){
    currentTester = test;
}

bool BackPropTutor::start(const TuteData &Data){

}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
