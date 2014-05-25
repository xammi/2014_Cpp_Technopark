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

    // Этот сигнал в принципе не нужен
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



    /*
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     */


    // WARNING! ONLY FOR DEBUG

    internalTest();


    /*
    try {
        InOutDataSet data;
        formInOutDataSet(data, keySet);

        for (int index : indexes) {
            tester->setTarget(nets[index]);
            tester->test(data);
        }
    } catch (Exception &exc) {
        emit showException(exc.toString());
    }
    */
}

void NetProcessor::onTeachNets(Ints indexes, QStringList keySet, TutorBoundaries boundaries) {
    qDebug() << "ura, teach";

    try {
        TuteData data;
        formTuteData(data, keySet);

        for (int index : indexes) {
            tester->setTarget(nets[index]);
            tutor->setNet(nets[index]);

            QString recArea;
            for (QString folder : keySet) {
                if(!recArea.contains(folder[0])){
                    recArea.append(folder[0]);
                }
//                QList<QImage> imgs;
//                QVector<QString> strs;
//                InputDataSet inputs;

//                dataStore->load(folder);
//                dataProc->prepareData(inputs, imgs);

            }
            nets[index]->setRecArea(recArea);

            tutor->setLimits(boundaries);

            // Needs to be correct!
            tutor->start(data, "&");
        }
    }  catch (Exception &exc) {
        emit showException(exc.toString());
    }
}

void NetProcessor::formInOutDataSet(InOutDataSet &, const QStringList &) {
    throw WrongFileFormat();
}

void NetProcessor::formTuteData(TuteData &, const QStringList &) {
    throw WrongFileFormat();
}

//-------------------------------------------------------------------------------------------------
void NetProcessor::internalTest() {
    if (nets.size() == 0) return;

    tester->setTarget(nets[0]);
    tutor->setNet(nets[0]);


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

    packOne.inputs = {one};
    packOne.outputs = {oneOut};

    packTwo.outputs = {twoOut};
    packTwo.inputs = {two};


    TuteData data = {packOne, packTwo};

    TutorBoundaries b(0.001, 0.0001, 100, 100000000, 1);

    tutor->setLimits(b);
    tutor->start(data, "54");

    DataProcess::InputData checker;
    InputDataSet ins;
    checker.values.resize(21);

    checker.values = {0,1,1,1,
                      0,1,0,0,
                      0,1,1,1,
                      0,0,0,1,
                      0,1,1,1,
                      1};
    ins.append(&checker);


    DataProcess::InputData checker1;
    checker1.values = {1,1,1,1,
                      1,0,0,0,
                      1,1,1,1,
                      0,0,0,1,
                      1,1,1,1,
                      1};
    ins.append(&checker1);


    DataProcess::InputData checker2;
    checker2.values = {1,0,0,1,
                      1,0,0,1,
                      1,0,0,1,
                      1,1,1,1,
                      0,0,0,1,
                      1};

    ins.append(&checker2);

    QString answer = tester->test(ins);
    qDebug() << answer << endl;
}

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
