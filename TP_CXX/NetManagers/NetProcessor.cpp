#include "NetProcessor.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
NetProcessor::NetProcessor(QString dir)
    :   netsCatalog(dir), gui(new NeuNetUI)
{
    this->setDefaultConf();
    this->connectUI();

    this->loadAllNets();
    gui->show();
}

void NetProcessor::loadAllNets() {
    QDir qdir(netsCatalog);
    QStringList listFiles = qdir.entryList(QDir::Files);

    try {
        for (QString file : listFiles)
            if (file.contains(".net"))
                nets.append(factory->createFromFile(qdir.absoluteFilePath(file)));
    } catch (Exception & exc) {
        emit showException(exc.toString());
    }

    this->onUpdateNets(gui->getNetsView());
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
    dataStore = new DataProcess::FileStorage;
    dataProc = new DataProcess::ImageProcessor;

    tester = new Tester;
    tutor = new NetTutors::BackPropTutor(tester);
    factory = new Factory::MultiLayerFactory;
    destroyer = new Factory::MultiLayerDestroyer;

    dataStore->onUpdate(gui->getDataView());
}

void NetProcessor::connectUI() {
    connect(gui, SIGNAL(loadNet(QString)), SLOT(onLoadNet(QString)));
    connect(gui, SIGNAL(createNets(QString, QString, NCounts)), SLOT(onCreateNets(QString, QString, NCounts)));
    connect(gui, SIGNAL(saveNet(QString, CIndex)), SLOT(onSaveNet(QString, CIndex)));
    connect(gui, SIGNAL(removeNet(CIndex)), SLOT(onRemoveNet(CIndex)));

    connect(gui, SIGNAL(updateNets(QTableWidget*)), SLOT(onUpdateNets(QTableWidget*)));
    connect(gui, SIGNAL(updateData(QTreeWidget*)), dataStore, SLOT(onUpdate(QTreeWidget*)));

    connect(this, SIGNAL(showInfo(QString)), gui, SLOT(onShowInfo(QString)));
    connect(this, SIGNAL(showException(QString)), gui, SLOT(onShowException(QString)));
    connect(this, SIGNAL(showDebug(QString)), gui, SLOT(onShowDebug(QString)));
    connect(tester, SIGNAL(toDebug(QString)), SIGNAL(showDebug(QString)));
    connect(tutor, SIGNAL(toDebug(QString)), SIGNAL(showDebug(QString)));

    connect(gui, SIGNAL(testNets()), SLOT(onTestNets()));
    connect(gui, SIGNAL(teachNets()), SLOT(onTeachNets()));
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
        destroyer->writeNetToFile(toSave, netsCatalog + filename);
        emit showInfo("Successfully saved");
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
    for (AbstractNet *net: nets) {
        view->setItem(row, 0, new QTableWidgetItem(net->name()));
        view->setItem(row, 1, new QTableWidgetItem(net->topology()));
        row++;
    }
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::onTestNets() {}


void NetProcessor::onTeachNets() {
    if (nets.size() == 0) return;

    tester->setTarget(nets[0]);
    tutor->setNet(nets[0]);

    TuteData data;
    InOutDataSet pack;

    // Смотрим сеть с композицией 3-2-2

    DataProcess::InputData *one = new DataProcess::InputData();
    one->values.resize(3);
    one->values[0] = 1;
    one->values[1] = 0;
    one->values[2] = 0;

    DataProcess::InputData *two = new DataProcess::InputData();
    two->values.resize(3);
    two->values[0] = 0;
    two->values[1] = 0;
    two->values[2] = 1;

    DataProcess::OutputData *oneOut = new DataProcess::OutputData();
    oneOut->values.resize(2);
    oneOut->values[0] = 1;
    oneOut->values[1] = 0;

    DataProcess::OutputData *twoOut = new DataProcess::OutputData();
    twoOut->values.resize(2);
    twoOut->values[0] = 0;
    twoOut->values[1] = 1;

    pack.inputs.append(one);
    pack.outputs.append(oneOut);
    data.runData.append(pack);

    pack.inputs.clear();
    pack.outputs.clear();

    pack.outputs.append(twoOut);
    pack.inputs.append(two);
    data.runData.append(pack);


    tutor->start(data);
}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
