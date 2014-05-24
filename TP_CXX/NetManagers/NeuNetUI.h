#ifndef NEUNETUI_H
#define NEUNETUI_H

#include <QMainWindow>
#include <QDialog>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QTreeWidget>

#include "Factory/BuildInfo.h"
#include "../includes.h"

namespace Ui {
    class NeuNetUI;
    class CreateNetUI;
    class AddLimitsUI;
    class AddSetUI;
}

namespace NetManagers {

    using namespace BuildData;

    const QString DEFAULT_NETS_DIR = "../TP_CXX/Nets data";

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class NeuNetUI : public QMainWindow {
    Q_OBJECT
    
signals:
    void loadNet(QString);
    void createNets(QString, QString, NCounts);
    void saveNet(QString, CIndex);
    void removeNet(CIndex);

    void updateNets(QTableWidget *);
    void updateData(QTreeWidget *);

    void addData(QString);
    void removeData();
    void formDataSet();
    void refreshData();

    void testNets();
    void teachNets();

public slots:
    void onShowInfo(QString);
    void onShowException(QString);
    void onShowDebug(QString);

private slots:
    void onLimitsShow();
    void onCreateShow();
    void onCreateNets();

    void onLoadNets(QStringList);
    void onSaveNets();
    void onRemoveNets();

    void onAddShow();
    void onAddData();
    void onRefreshData();
    void onRemoveData();
    void onCombineData();

    void onTeachNets();

public:
    explicit NeuNetUI(QWidget *parent = 0);
    virtual ~NeuNetUI();

    QTreeWidget * getDataView() const;
    QTableWidget * getNetsView() const;
    
private:
    void adjustUi();
    void updateUI();

    Ui::NeuNetUI *ui;
    QFileDialog *openDlg;

    Ui::CreateNetUI *createUi;
    QDialog *createDlg;

    Ui::AddLimitsUI *addLimitsUi;
    QDialog *addLimitsDlg;

    QRegExpValidator *createValidator;


    QRegExpValidator *addLimitsValidator;

    Ui::AddSetUI *addSetUi;
    QDialog *addSetDlg;
    QRegExpValidator *addSetValidator;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NEUNETUI_H
