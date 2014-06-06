#ifndef NEUNETUI_H
#define NEUNETUI_H

#include <QMainWindow>
#include <QDialog>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSet>

#include "Factory/BuildInfo.h"
#include "../NetTutors/TuteData.h"
#include "../includes.h"

namespace Ui {
    class NeuNetUI;
    class CreateNetUI;
    class AddLimitsUI;
}

namespace NetManagers {

    using namespace BuildData;
    using NetTutors::TuteBoundaries;

    const QString DEFAULT_NETS_DIR = "../TP_CXX/Nets data/";

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class NeuNetUI : public QMainWindow {
    Q_OBJECT
    
    int processTimer;

signals:
    void loadNet(QString);
    void createNets(QString, QString, NCounts);
    void saveNet(QString, CIndex);
    void removeNet(CIndex);

    void updateNets(QTableWidget *);
    void updateData(QTreeWidget *);

    void refreshData();

    void testNets(Ints, QStringList);
    void tuteNets(Ints, QStringList, TuteBoundaries);

public slots:
    void onShowInfo(QString);
    void onShowException(QString);
    void onShowDebug(QString);

    void onRequestUpdate();
    void onTuteStarted(Index);
    void onTuteFinished(Index);

private slots:
    void onLimitsShow();
    void onCreateShow();
    void onCreateNets();

    void onLoadNets(QStringList);
    void onSaveNets();
    void onRemoveNets();

    void onRefreshData();

    void onTestNets();
    void onTuteNets();

public:
    explicit NeuNetUI(QWidget *parent = 0);
    virtual ~NeuNetUI();

    QTreeWidget * getDataView() const;
    QTableWidget * getNetsView() const;
    
private:
    void adjustUi();
    void setDefaultConf();
    void updateUI();

    void timerEvent(QTimerEvent *);
    void selectedNets(Ints &) const;

    Ui::NeuNetUI *ui;
    QFileDialog *openDlg;

    Ui::CreateNetUI *createUi;
    QDialog *createDlg;
    QRegExpValidator *createValidator;

    Ui::AddLimitsUI *addLimitsUi;
    QDialog *addLimitsDlg;

    QSet<int> tuteNow;
};

//-------------------------------------------------------------------------------------------------
struct AlreadyTute : public Exception {
    QString toString() { return QString("еть уже на обучении"); }
};

//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NEUNETUI_H
