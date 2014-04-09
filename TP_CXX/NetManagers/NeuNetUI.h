#ifndef NEUNETUI_H
#define NEUNETUI_H

#include <QMainWindow>
#include "../includes.h"

namespace Ui {
    class NeuNetUI;
}

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
class NeuNetUI : public QMainWindow {
    Q_OBJECT
    
signals:
    void onLoadNet();
    void onCreateNet();
    void onCreateTopology();

    void onAddData();
    void onRemoveData();
    void onFormDataSet();

    void onTestNetSingle();
    void onTestNetDataSet();

    void onTeachNet();
    void onSaveNet();
    void onRemoveNet();

public:
    explicit NeuNetUI(QWidget *parent = 0);
    ~NeuNetUI();
    
private:
    Ui::NeuNetUI *ui;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NEUNETUI_H
