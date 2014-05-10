#ifndef NEUNETUI_H
#define NEUNETUI_H

#include <QMainWindow>
#include <QDialog>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QMessageBox>

#include "../includes.h"

namespace Ui {
    class NeuNetUI;
    class CreateNetUI;
}

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
enum NumOrRange { NUM, RANGE };

struct NCount {
    NCount() {}
    NCount(const int);
    NCount(const int, const int);

    union {
        int cnt;
        struct {
            int from;
            int to;
        };
    };
    NumOrRange type;
};
typedef QVector<NCount> NCounts;
//-------------------------------------------------------------------------------------------------
class NeuNetUI : public QMainWindow {
    Q_OBJECT
    
signals:
    void loadNet(QString);
    void createNets(int, NCounts);
    void saveNet(QString, CIndex);
    void removeNet(CIndex);

    void addData();
    void removeData();
    void formDataSet();

    void testNetSingle();
    void testNetDataSet();
    void teachNet();

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
    void createError(const QString &, int selFrom = 0, int selAmount = 0);
    void createNetRecord(const QString &, const QString &);

    Ui::NeuNetUI *ui;
    QFileDialog *openDlg;

    Ui::CreateNetUI *createUi;
    QDialog *createDlg;
    QRegExpValidator *createValidator;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NEUNETUI_H
