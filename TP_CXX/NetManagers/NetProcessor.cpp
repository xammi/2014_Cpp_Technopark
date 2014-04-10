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

void NetProcessor::setDefaultConf() {
    tester = new Tester;
    tutor = new BackPropTutor;
    dataStore = new ImageStorage;
    dataProc = new ImageProcessor;
}

void NetProcessor::connectUI() {
    connect(gui, SIGNAL(onLoadNet()), SLOT(onLoadNet()));
    connect(gui, SIGNAL(onCreateNet()), SLOT(onCreateNet()));
    connect(gui, SIGNAL(onCreateTopology()), SLOT(onCreateTopology()));

    connect(gui, SIGNAL(onAddData()), SLOT(onAddData()));
    connect(gui, SIGNAL(onRemoveData()), SLOT(onRemoveData()));
    connect(gui, SIGNAL(onFormDataSet()), SLOT(onFormDataSet()));

    connect(gui, SIGNAL(onTestNetSingle()), SLOT(onTestNetSingle()));
    connect(gui, SIGNAL(onTestNetDataSet()), SLOT(onTestNetDataSet()));

    connect(gui, SIGNAL(onTeachNet()), SLOT(onTeachNet()));
    connect(gui, SIGNAL(onSaveNet()), SLOT(onSaveNet()));
    connect(gui, SIGNAL(onRemoveNet()), SLOT(onRemoveNet()));
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::onLoadNet() {}
void NetProcessor::onCreateNet() {}
void NetProcessor::onCreateTopology() {}

void NetProcessor::onAddData() {}
void NetProcessor::onRemoveData() {}
void NetProcessor::onFormDataSet() {}

void NetProcessor::onTestNetSingle() {}
void NetProcessor::onTestNetDataSet() {}

void NetProcessor::onTeachNet() {}
void NetProcessor::onSaveNet() {}
void NetProcessor::onRemoveNet() {}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
