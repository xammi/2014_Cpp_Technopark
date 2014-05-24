#ifndef NETPROCESSOR_H
#define NETPROCESSOR_H

#include "NeuNetUI.h"
#include "Tester.h"

#include "../DataProcess/FileStorage.h"
#include "../DataProcess/ImageProcessor.h"

#include "../NetTutors/BackPropTutor.h"
#include "../Factory/MultiLayerDestroyer.h"
#include "../Factory/MultiLayerFactory.h"
#include "../NeuNet/MultiLayerNet.h"

namespace NetManagers {

    using namespace BuildData;
    using namespace Factory;
    using namespace NetTutors;
    using namespace DataProcess;

    using NeuNets::AbstractNet;

//-------------------------------------------------------------------------------------------------
class NetProcessor : public QObject {

    Q_OBJECT

private slots:
    void onLoadNet(QString);
    void onSaveNet(QString, CIndex);
    void onRemoveNet(CIndex);
    void onCreateNets(QString, QString, NCounts);

    void onUpdateNets(QTableWidget *);

    void onAddData(QString);
    void onRemoveData();
    void onFormDataSet();

    void onTestNets();
    void onTeachNets();

signals:
    void showInfo(QString);
    void showException(QString);
    void showDebug(QString);

public:
    static const NetProcessor & get_self();

protected:
    NetProcessor(QString dir = DEFAULT_NETS_DIR);
    ~NetProcessor();

    void loadAllNets();
    void setDefaultConf();
    void connectUI();

private:
    const QString netsCatalog;

    NeuNetUI *gui;
    Tester *tester;
    AbstractTutor *tutor;

    FileStorage *dataStore;
    AbstractProcessor *dataProc;

    PtrVector<AbstractNet> nets;

    AbstractFactory *factory;
    AbstractDestroyer *destroyer;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NETPROCESSOR_H
