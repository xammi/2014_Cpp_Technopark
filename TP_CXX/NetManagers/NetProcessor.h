#ifndef NETPROCESSOR_H
#define NETPROCESSOR_H

#include "NeuNetUI.h"
#include "Tester.h"

#include "../DataProcess/ImageStorage.h"
#include "../DataProcess/ImageProcessor.h"

#include "../NetTutors/BackPropTutor.h"
#include "../Factory/MultiLayerDestroyer.h"
#include "../Factory/MultiLayerFactory.h"
#include "../NeuNet/MultiLayerNet.h"

namespace NetManagers {

    using namespace BuildData;

    using DataProcess::AbstractStorage;
    using DataProcess::AbstractProcessor;

    using NetTutors::AbstractTutor;
    using NeuNets::AbstractNet;
    using Factory::AbstractNetFactory;
    using Factory::AbstractNetDestroyer;

//-------------------------------------------------------------------------------------------------
class NetProcessor : public QObject {

    Q_OBJECT

private slots:
    void onLoadNet(QString);
    void onSaveNet(QString, CIndex);
    void onRemoveNet(CIndex);
    void onCreateNets(int, NCounts);

    void onUpdateNets(QTableWidget *);
    void onUpdateData(QTreeWidget *);

    void onAddData();
    void onRemoveData();
    void onFormDataSet();

    void onTestNetSingle();
    void onTestNetDataSet();

    void onTeachNet();

signals:
    void showException(QString);
    void showDebug(QString);

public:
    static const NetProcessor & get_self();

protected:
    NetProcessor();
    ~NetProcessor();

    void setDefaultConf();
    void connectUI();

private:
    NeuNetUI *gui;
    Tester *tester;
    AbstractTutor *tutor;

    AbstractStorage *dataStore;
    AbstractProcessor *dataProc;

    PtrVector<AbstractNet> nets;

    AbstractNetFactory *factory;
    AbstractNetDestroyer *destroyer;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NETPROCESSOR_H
