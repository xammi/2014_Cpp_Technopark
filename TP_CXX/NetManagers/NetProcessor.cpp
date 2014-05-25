#include "NetProcessor.h"
#include <iostream>

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
    if (dataStore) delete dataStore;
    if (dataProc) delete dataProc;

    if (gui) delete gui;
    if (tester) delete tester;
    if (tutor) delete tutor;

    if (factory) delete factory;
    if (destroyer) delete destroyer;
}
//-------------------------------------------------------------------------------------------------
const NetProcessor & NetProcessor::get_self() {
    static NetProcessor self;
    return self;
}

void NetProcessor::setDefaultConf() {
    try {
        ImageProcessor * imgProc = new DataProcess::ImageProcessor;
        dataStore = new DataProcess::FileStorage(imgProc);
        dataProc = imgProc;

        tester = new Tester;
        tutor = new NetTutors::BackPropTutor(tester);
        factory = new Factory::MultiLayerFactory;
        destroyer = new Factory::MultiLayerDestroyer;

        dataStore->onUpdate(gui->getDataView());

    } catch (Exception &) {
        this->~NetProcessor();
        throw;
    } catch (std::bad_alloc &) {
        this->~NetProcessor();
        throw;
    }
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

    connect(gui, SIGNAL(testNets(Ints, QStringList)), SLOT(onTestNets(Ints, QStringList)));
    connect(gui, SIGNAL(teachNets(Ints, QStringList, TutorBoundaries)), SLOT(onTeachNets(Ints, QStringList, TutorBoundaries)));
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

        QString recArea;
        for (QChar ch : net->getRecArea())
            recArea = recArea + ch +  ", ";

        view->setItem(row, 0, new QTableWidgetItem(net->name()));
        view->setItem(row, 1, new QTableWidgetItem(net->topology()));
        view->setItem(row, 2, new QTableWidgetItem(recArea));
        row++;
    }
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::onTestNets(Ints indexes, QStringList keySet) {
    qDebug() << "ura, test";

    try {
        InOutDataSet data;

        for (int index : indexes) {
            tester->setTarget(nets[index]);
            tester->test(data);
        }
    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::onTeachNets(Ints indexes, QStringList keySet, TutorBoundaries boundaries) {
    try {


    }  catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::internalTest() {
    if (nets.size() == 0) return;

    tester->setTarget(nets[0]);
    tutor->setNet(nets[0]);

    // Смотрим сеть с композицией 3-2-2  WORKS
    // Смотрим сеть с композицией 3-3-2  WORKS
    // Смотрим сеть с композицией 5-4-2  WORKS

    InputData *one = new InputData();
    one->values = {1,1,1,1,
                   1,0,0,0,
                   1,1,1,1,
                   0,0,0,1,
                   1,1,1,1,
                   1};

    OutputData *oneOut = new OutputData();
    oneOut->values = {1,0};

    InputData *two = new InputData();
    two->values = {1,0,0,1,
                   1,0,0,1,
                   1,1,1,1,
                   0,0,0,1,
                   0,0,0,1,
                   1};

    OutputData *twoOut = new OutputData();
    twoOut->values = {0,1};

    InOutDataSet packOne, packTwo;

    packOne.inputs.append(one);
    packOne.outputs.append(oneOut);

    packTwo.outputs.append(twoOut);
    packTwo.inputs.append(two);

    TuteData data = {packOne, packTwo};

    TutorBoundaries b(0.001, 0.0001, 100, 100000000, 1);

    tutor->setLimits(b);
    tutor->start(data);
}

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
