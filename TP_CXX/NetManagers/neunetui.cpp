#include "neunetui.h"
#include "ui_neunetui.h"

namespace NetManagers {
//-------------------------------------------------------------------------------------------------
NeuNetUI::NeuNetUI(QWidget *parent)
    :    QMainWindow(parent), ui(new Ui::NeuNetUI)
{
    ui->setupUi(this);
}

NeuNetUI::~NeuNetUI() {
    delete ui;
}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
