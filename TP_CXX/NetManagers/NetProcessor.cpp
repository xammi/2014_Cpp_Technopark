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

    if (factory) delete factory;
    if (destroyer) delete destroyer;

    for (AbstractNet * net : nets)
        if (net)
            delete net;
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

        factory = new Factory::MultiLayerFactory;
        destroyer = new Factory::MultiLayerDestroyer;

        emit requestUpdate();
        // dataStore->onUpdate(gui->getDataView());

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

    connect(this, SIGNAL(requestUpdate()), gui, SLOT(onRequestUpdate()));

    connect(gui, SIGNAL(testNets(Ints, QStringList)), SLOT(onTestNets(Ints, QStringList)));
    connect(gui, SIGNAL(teachNets(Ints, QStringList, TuteBoundaries)), SLOT(onTeachNets(Ints, QStringList, TuteBoundaries)));
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
        Tester tester;
        InputDataSet inputSet;
        dataStore->loadFiles(inputSet, keySet);

        for (int index : indexes) {
            tester.setTarget(nets[index]);
            tester.test(inputSet);
        }

        for (InputData * input : inputSet)
            if (input)
                delete input;

    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::onTeachNets(Ints indexes, QStringList keySet, TuteBoundaries boundaries) {
    try {
        TuteData ttdata;
        prepareTuteData(ttdata, indexes, keySet);

        TuteModule *module;
        for (int index : indexes) {
            module = new TuteModule <BackPropTutor> (nets[index], ttdata, boundaries);

            connect(module, SIGNAL(toException(QString)), SIGNAL(showException(QString)));
            connect(module, SIGNAL(toDebug(QString)), SIGNAL(showDebug(QString)));
            connect(module, SIGNAL(finished()), SIGNAL(requestUpdate()));

            QThreadPool::globalInstance()->start(module);
        }

    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}


void NetProcessor::prepareTuteData(TuteData & ttdata, const Ints & indexes, const QStringList & keySet) {
    dataStore->loadDirs(ttdata.inputs, keySet);

    Ints amounts;
    amounts.fill(0, ttdata.inputs.size());
    for (int I = 0; I < ttdata.inputs.size(); ++I)
        amounts[I] = ttdata.inputs[I].size();

    for (int index : indexes) {

        QString recArea;
        for (QString folder : keySet)
            if(!recArea.contains(folder[0]))
                recArea.append(folder[0]);

        nets[index]->setRecArea(recArea);

        OutputDataSet outputs;
        nets[index]->getOutDataSet(outputs, recArea);

        OutputDataSet duplicOutputs;
        for (int I = 0; I < outputs.size(); ++I) {
            duplicOutputs.clear();
            for (int J = 0; J < amounts[I]; ++J)
                duplicOutputs.append(outputs[I]);
            ttdata.outputs.append(duplicOutputs);
        }
    }
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::internalTest() {
//    if (nets.size() == 0) return;

//    tester->setTarget(nets[0]);
//    tutor->setNet(nets[0]);


//    InputData *one = new InputData();
//    one->values = {1,1,1,1,
//                   1,0,0,0,
//                   1,1,1,1,
//                   0,0,0,1,
//                   1,1,1,1,
//                   1};

//    OutputData *oneOut = new OutputData();
//    oneOut->values = {1,0};

//    InputData *two = new InputData();
//    two->values = {1,0,0,1,
//                   1,0,0,1,
//                   1,1,1,1,
//                   0,0,0,1,
//                   0,0,0,1,
//                   1};

//    OutputData *twoOut = new OutputData();
//    twoOut->values = {0,1};

//    InOutDataSet packOne, packTwo;

//    packOne.inputs.append(one);
//    packOne.outputs.append(oneOut);

//    packTwo.outputs.append(twoOut);
//    packTwo.inputs.append(two);

//    TuteData data = {packOne, packTwo};

//    TutorBoundaries b(0.001, 0.0001, 100, 100000000, 1);

//    tutor->setLimits(b);
//    tutor->start(data);

//    DataProcess::InputData checker;
//    InputDataSet ins;
//    checker.values.resize(21);

//    checker.values = {0,1,1,1,
//                      0,1,0,0,
//                      0,1,1,1,
//                      0,0,0,1,
//                      0,1,1,1,
//                      1};
//    ins.append(&checker);


//    DataProcess::InputData checker1;
//    checker1.values = {1,1,1,1,
//                      1,0,0,0,
//                      1,1,1,1,
//                      0,0,0,1,
//                      1,1,1,1,
//                      1};
//    ins.append(&checker1);


//    DataProcess::InputData checker2;
//    checker2.values = {1,0,0,1,
//                      1,0,0,1,
//                      1,0,0,1,
//                      1,1,1,1,
//                      0,0,0,1,
//                      1};

//    ins.append(&checker2);

//    QString answer = tester->test(ins);
//    qDebug() << answer << endl;
}

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
