#ifndef NETPROCESSOR_H
#define NETPROCESSOR_H

#include "NeuNetUI.h"
#include "Tester.h"

#include "../DataProcess/FileStorage.h"
#include "../DataProcess/ImageProcessor.h"

#include "../NetTutors/BackPropTutor.h"
#include "../NetTutors/TuteModule.h"

#include "../Factory/MultiLayerDestroyer.h"
#include "../Factory/MultiLayerFactory.h"
#include "../NeuNet/MultiLayerNet.h"

#include <QThreadPool>

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

    void onTestNets(Ints, QStringList);
    void onTuteNets(Ints, QStringList, TuteBoundaries);

signals:
    void showInfo(QString);
    void showException(QString);
    void showDebug(QString);

    void requestUpdate();
    void tuteStarted(int);
    void tuteFinished(int);

public:
    static const NetProcessor & get_self();

private:
    NetProcessor(QString dir = DEFAULT_NETS_DIR);
    ~NetProcessor();

    void loadAllNets();
    void setDefaultConf();
    void connectUI();

    TuteModule * createTuteModule(Index);
    void prepareTuteData(TuteData &, const Ints &, const QStringList &);

private:
    const QString netsCatalog;

    NeuNetUI *gui;

    FileStorage *dataStore;
    AbstractProcessor *dataProc;

    QVector<AbstractNet *> nets;

    AbstractFactory *factory;
    AbstractDestroyer *destroyer;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NETPROCESSOR_H
