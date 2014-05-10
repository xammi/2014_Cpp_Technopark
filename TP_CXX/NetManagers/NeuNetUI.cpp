#include "NeuNetUI.h"
#include "ui_neunetui.h"
#include "ui_createNet.h"

namespace NetManagers {

NCount::NCount(const int _cnt)
    :   cnt(_cnt), type(NUM) {}

NCount::NCount(const int range_from, const int range_to)
    :   from(range_from), to(range_to), type(RANGE) {}
//-------------------------------------------------------------------------------------------------
NeuNetUI::NeuNetUI(QWidget *parent) :
      QMainWindow(parent), ui(new Ui::NeuNetUI),
      openDlg(new QFileDialog(this)),
      createUi(new Ui::CreateNetUI), createDlg(new QDialog(this)),
      createValidator(new QRegExpValidator(QRegExp("([0-9]+,|[0-9]+-[0-9]+,)+")))
{
    ui->setupUi(this);
    createUi->setupUi(createDlg);

    this->adjustUi();
    this->setWindowState(Qt::WindowMaximized);
}

void NeuNetUI::adjustUi() {
    connect(ui->netCreate, SIGNAL(pressed()), SLOT(onCreateShow()));
    connect(createUi->ok, SIGNAL(pressed()), SLOT(onCreateNets()));
    connect(createUi->cancel, SIGNAL(pressed()), createDlg, SLOT(hide()));
    createUi->neurons->setValidator(createValidator);

    connect(ui->netLoad, SIGNAL(pressed()), openDlg, SLOT(show()));
    connect(openDlg, SIGNAL(filesSelected(QStringList)), SLOT(onLoadNets(QStringList)));
    connect(ui->netSave, SIGNAL(pressed()), SLOT(onSaveNets()));
    connect(ui->netRemove, SIGNAL(pressed()), SLOT(onRemoveNets()));
}

NeuNetUI::~NeuNetUI() {
    delete ui;
}
//-------------------------------------------------------------------------------------------------
void NeuNetUI::onLoadNets(QStringList files) {
    foreach (QString file, files)
        if (file.contains(".net")) {
            emit loadNet(file);
        } else {
            QMessageBox msgBox;
            msgBox.setText("You can only load .net files.");
            msgBox.exec();
        }
}

void NeuNetUI::onSaveNets() {
    foreach (QTableWidgetItem * item, ui->nets->selectedItems())
        if (item->column() == 0)
            emit saveNet(item->text() + ".net", item->row());
}

void NeuNetUI::onRemoveNets() {
    QList<QTableWidgetItem *> items = ui->nets->selectedItems();

    for (int I = 0; I < items.size(); ++I)
        if (items[I] && items[I]->column() == 0) {
            emit removeNet(items[I]->row());
            ui->nets->removeRow(items[I]->row());
            items[I + 1] = NULL;
        }
}
//-------------------------------------------------------------------------------------------------
void NeuNetUI::onCreateShow() {
    createUi->name->setText("");
    createUi->layersCnt->setValue(1);
    createUi->neurons->setText("");
    createDlg->show();
}

void NeuNetUI::onCreateNets() {
    QString name = createUi->name->text();
    if (name == "")
        name = "Net # " + QString::number(ui->nets->rowCount());

    foreach (QTableWidgetItem * item, ui->nets->selectedItems())
        if (item->column() == 0)
            if (name == item->text()) {
                createUi->errors->setText("Name must be unique");
                return;
            }

    int layersCnt = createUi->layersCnt->value();

    QString nData = createUi->neurons->text();
    if (nData == "") {
        createUi->errors->setText("Empty field");
        return;
    }

    QStringList nDataList = nData.split(',');
    if (layersCnt != nDataList.size()) {
        createUi->errors->setText("Wrong count of neuron data");
        return;
    }

    NCounts neuronsCnt;
    foreach (QString item, nDataList) {
        if (item.contains("-")) {
            int range_from = item.split("-")[0].toInt();
            int range_to = item.split("-")[1].toInt();

            if (range_from > range_to) {
                createUi->errors->setText("Wrong range");
                return;
            }

            neuronsCnt.append(NCount(range_from, range_to));
        } else
            neuronsCnt.append(NCount(item.toInt()));
    }

    createNetRecord(name, nData);

    emit createNets(layersCnt, neuronsCnt);
    createDlg->hide();
}

void NeuNetUI::createNetRecord(const QString & name, const QString & topology) {
    int row = ui->nets->rowCount();
    ui->nets->setRowCount(row + 1);
    ui->nets->setItem(row, 0, new QTableWidgetItem(name));
    ui->nets->setItem(row, 1, new QTableWidgetItem(topology));
}
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
