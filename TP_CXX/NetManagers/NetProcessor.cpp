#include "NetProcessor.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
NetProcessor::NetProcessor()
    :   gui(new NeuNetUI)
{
    this->setDefaultConf();
    gui->show();
}

NetProcessor::~NetProcessor() {
    delete gui;
    delete tester;
    delete dataStore;
    delete dataProc;
}
//-------------------------------------------------------------------------------------------------
const NetProcessor & NetProcessor::get_self() {
    static NetProcessor self;
    return self;
}

void setDefaultConf() {
    tester = new Tester;
    tutor = new BackPropTutor;
    dataStore = new ImageStore;
    dataProc = new ImageProcessor;
}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
