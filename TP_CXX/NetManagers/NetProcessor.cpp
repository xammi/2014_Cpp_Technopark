#include "NetProcessor.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
NetProcessor::NetProcessor()
    :   gui(new NeuNetUI)
{
    this->setDefaultConf();
    this->connectUI();
    gui->show();
}

NetProcessor::~NetProcessor() {
    delete dataStore;
    delete dataProc;

    delete gui;
    delete tester;
    delete tutor;

    delete factory;
    delete destroyer;
}
//-------------------------------------------------------------------------------------------------
const NetProcessor & NetProcessor::get_self() {
    static NetProcessor self;
    return self;
}

void NetProcessor::setDefaultConf() {
    dataStore = new DataProcess::ImageStorage;
    dataProc = new DataProcess::ImageProcessor;

    tester = new Tester;
    tutor = new NetTutors::BackPropTutor;
    factory = new Factory::MultiLayerFactory;
    destroyer = new Factory::MultiLayerDestroyer;
}

void NetProcessor::connectUI() {
    connect(gui, SIGNAL(loadNet(QString)), SLOT(onLoadNet(QString)));
    connect(gui, SIGNAL(createNets(QString, QString, NCounts)), SLOT(onCreateNets(QString, QString, NCounts)));
    connect(gui, SIGNAL(saveNet(QString, CIndex)), SLOT(onSaveNet(QString, CIndex)));
    connect(gui, SIGNAL(removeNet(CIndex)), SLOT(onRemoveNet(CIndex)));

    connect(gui, SIGNAL(updateNets(QTableWidget*)), SLOT(onUpdateNets(QTableWidget*)));
    connect(gui, SIGNAL(updateData(QTreeWidget*)), SLOT(onUpdateData(QTreeWidget*)));

    connect(this, SIGNAL(showException(QString)), gui, SLOT(onShowException(QString)));
    connect(this, SIGNAL(showDebug(QString)), gui, SLOT(onShowDebug(QString)));
    connect(tester, SIGNAL(toDebug(QString)), SIGNAL(showDebug(QString)));
    connect(tutor, SIGNAL(toDebug(QString)), SIGNAL(showDebug(QString)));

    connect(gui, SIGNAL(addData()), SLOT(onAddData()));
    connect(gui, SIGNAL(removeData()), SLOT(onRemoveData()));
    connect(gui, SIGNAL(formDataSet()), SLOT(onFormDataSet()));

    connect(gui, SIGNAL(testNetSingle()), SLOT(onTestNetSingle()));
    connect(gui, SIGNAL(testNetDataSet()), SLOT(onTestNetDataSet()));
    connect(gui, SIGNAL(teachNet()), SLOT(onTeachNet()));
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::onLoadNet(QString filename) {
    try {
        AbstractNet *loaded = factory->createFromFile(filename);
        nets.append(loaded);
    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::onCreateNets(QString name, QString funcName, NCounts cnts) {
    try {
        factory->createFromInfo(name, funcName, cnts, nets);
    } catch(Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::onSaveNet(QString filename, CIndex netIndex) {
    try {
        AbstractNet *toSave = nets[netIndex];
        destroyer->writeNetToFile(toSave, filename);
    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::onRemoveNet(CIndex index) {
    try {
        destroyer->destroy(nets[index]);
        nets.remove(index);
    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::onUpdateNets(QTableWidget * view) {
    view->clearContents();
    view->setRowCount(nets.size());

    int row = 0;
    foreach (AbstractNet *net, nets) {
        view->setItem(row, 0, new QTableWidgetItem(net->name()));
        view->setItem(row, 1, new QTableWidgetItem(net->topology()));
        row++;
    }
}
//-------------------------------------------------------------------------------------------------
void NetProcessor::onAddData() {}
void NetProcessor::onRemoveData() {}
void NetProcessor::onFormDataSet() {}
void NetProcessor::onUpdateData(QTreeWidget *) {}

void NetProcessor::onTestNetSingle() {}
void NetProcessor::onTestNetDataSet() {}
void NetProcessor::onTeachNet() {}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
