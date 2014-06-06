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
    emit requestUpdate();

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

    bool waitResult = QThreadPool::globalInstance()->waitForDone();
    if (! waitResult) {
        qDebug() << "Problems with closing the threads";
    }
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
    connect(gui, SIGNAL(tuteNets(Ints, QStringList, TuteBoundaries)), SLOT(onTuteNets(Ints, QStringList, TuteBoundaries)));

    connect(this, SIGNAL(tuteStarted(int)), gui, SLOT(onTuteStarted(int)));
    connect(this, SIGNAL(tuteFinished(int)), gui, SLOT(onTuteFinished(int)));
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
        connect(&tester, SIGNAL(toDebug(QString)), this, SIGNAL(showDebug(QString)));

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

void NetProcessor::onTuteNets(Ints indexes, QStringList keySet, TuteBoundaries boundaries) {
    try {
        TuteData ttdata;
        prepareTuteData(ttdata, indexes, keySet);

        QThreadPool *threadPool = QThreadPool::globalInstance();

        for (Index index : indexes) {
            TuteModule *module = createTuteModule(index);
            module->configure <BackPropTutor> (nets[index], ttdata, boundaries);
            threadPool->start(module);
        }

        // TODO: clearTuteData(ttdata);

    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

TuteModule * NetProcessor::createTuteModule(Index index) {
    TuteModule *module = new TuteModule(index);

    connect(module, SIGNAL(toException(QString)), this, SIGNAL(showException(QString)));
    connect(module, SIGNAL(toDebug(QString)), this, SIGNAL(showDebug(QString)));

    connect(module, SIGNAL(started(int)), this, SIGNAL(tuteStarted(int)));
    connect(module, SIGNAL(finished(int)), this, SIGNAL(tuteFinished(int)));
    connect(module, SIGNAL(finished(int)), this, SIGNAL(requestUpdate()));

    return module;
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
} // namespace NetManagers
