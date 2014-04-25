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
    /* Algorithm
     * 1. Send TuteData to Tester. Inside Tester - getResponse
     * Tute Data contains all necessary info for error counting.
     * Get Errors for each output drom Tester
     * Then get iterator from NN and BackPropagate
     *
     *
     *
     */



    return true;
}

//-------------------------------------------------------------------------------------------------
} // namespace Tutor
