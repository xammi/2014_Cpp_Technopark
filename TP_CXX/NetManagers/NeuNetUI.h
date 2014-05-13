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
}

namespace NetManagers {

    using namespace BuildData;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class NeuNetUI : public QMainWindow {
    Q_OBJECT
    
signals:
    void loadNet(QString);
    void createNets(int, NCounts);
    void saveNet(QString, CIndex);
    void removeNet(CIndex);

    void updateNets(QTableWidget *);
    void updateData(QTreeWidget *);

    void addData();
    void removeData();
    void formDataSet();

    void testNetSingle();
    void testNetDataSet();
    void teachNet();

public slots:
    void onShowException(QString);

private slots:
    void onCreateShow();
    void onCreateNets();

    void onLoadNets(QStringList);
    void onSaveNets();
    void onRemoveNets();

public:
    explicit NeuNetUI(QWidget *parent = 0);
    ~NeuNetUI();
    
private:
    void adjustUi();
    void updateUI();

    Ui::NeuNetUI *ui;
    QFileDialog *openDlg;

    Ui::CreateNetUI *createUi;
    QDialog *createDlg;
    QRegExpValidator *createValidator;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NEUNETUI_H
