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
    tutor = new NetTutors::BackPropTutor(tester);
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

    connect(this, SIGNAL(showInfo(QString)), gui, SLOT(onShowInfo(QString)));
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
void NetProcessor::onAddData() {}
void NetProcessor::onRemoveData() {}
void NetProcessor::onFormDataSet() {}
void NetProcessor::onUpdateData(QTreeWidget *) {}

//-------------------------------------------------------------------------------------------------
void NetProcessor::onTestNetSingle() {}
void NetProcessor::onTestNetDataSet() {}


void NetProcessor::onTeachNet() {
    if (nets.size() == 0) return;

    tester->setTarget(nets[0]);
    tutor->setNet(nets[0]);


    TuteData data;
    InOutDataSet pack;

    // Смотрим сеть с композицией 3-2-2  WORKS
    // Смотрим сеть с композицией 3-3-2  WORKS
    // Смотрим сеть с композицией 5-4-2  WORKS

    DataProcess::InputData *one = new DataProcess::InputData();
    one->values.resize(21);
    one->values[0] = 1;
    one->values[1] = 1;
    one->values[2] = 1;
    one->values[3] = 1;

    one->values[4] = 1;
    one->values[5] = 0;
    one->values[6] = 0;
    one->values[7] = 0;

    one->values[8] = 1;
    one->values[9] = 1;
    one->values[10] = 1;
    one->values[11] = 1;

    one->values[12] = 0;
    one->values[13] = 0;
    one->values[14] = 0;
    one->values[15] = 1;

    one->values[16] = 1;
    one->values[17] = 1;
    one->values[18] = 1;
    one->values[19] = 1;

    one->values[20] = 1;

    DataProcess::OutputData *oneOut = new DataProcess::OutputData();
    oneOut->values.resize(2);
    oneOut->values[0] = 1;
    oneOut->values[1] = 0;



    DataProcess::InputData *two = new DataProcess::InputData();
    two->values.resize(21);
    two->values[0] = 1;
    two->values[1] = 0;
    two->values[2] = 0;
    two->values[3] = 1;

    two->values[4] = 1;
    two->values[5] = 0;
    two->values[6] = 0;
    two->values[7] = 1;

    two->values[8] = 1;
    two->values[9] = 1;
    two->values[10] = 1;
    two->values[11] = 1;

    two->values[12] = 0;
    two->values[13] = 0;
    two->values[14] = 0;
    two->values[15] = 1;

    two->values[16] = 1;
    two->values[17] = 1;
    two->values[18] = 1;
    two->values[19] = 1;

    two->values[20] = 1;




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
