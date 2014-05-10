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
    connect(gui, SIGNAL(loadNet(QString)), SLOT(onLoadNet(QString)));
    connect(gui, SIGNAL(createNets(int, NCount)), SLOT(onCreateNets(int, NCount)));
    connect(gui, SIGNAL(saveNet(QString, CIndex)), SLOT(onSaveNet(QString, CIndex)));
    connect(gui, SIGNAL(removeNet(CIndex)), SLOT(onRemoveNet(CIndex)));

    connect(gui, SIGNAL(addData()), SLOT(onAddData()));
    connect(gui, SIGNAL(removeData()), SLOT(onRemoveData()));
    connect(gui, SIGNAL(formDataSet()), SLOT(onFormDataSet()));

    connect(gui, SIGNAL(testNetSingle()), SLOT(onTestNetSingle()));
    connect(gui, SIGNAL(testNetDataSet()), SLOT(onTestNetDataSet()));
    connect(gui, SIGNAL(teachNet()), SLOT(onTeachNet()));
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::onLoadNet(QString) {
    qDebug() << "on load";
}

void NetProcessor::onCreateNets(int, NCounts) {
    qDebug() << "on create";
}

void NetProcessor::onSaveNet(QString, CIndex) {
    qDebug() << "on save";
}

void NetProcessor::onRemoveNet(CIndex) {
    qDebug() << "on remove";
}
//-------------------------------------------------------------------------------------------------

void NetProcessor::onAddData() {}
void NetProcessor::onRemoveData() {}
void NetProcessor::onFormDataSet() {}

void NetProcessor::onTestNetSingle() {}
void NetProcessor::onTestNetDataSet() {}
void NetProcessor::onTeachNet() {}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
