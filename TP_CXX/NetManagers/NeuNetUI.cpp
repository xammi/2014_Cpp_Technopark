#include "NeuNetUI.h"
#include "ui_neunetui.h"
#include "ui_createNet.h"
#include "ui_addSet.h"
#include "ui_addLimits.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
NeuNetUI::NeuNetUI(QWidget *parent) :
      QMainWindow(parent), ui(new Ui::NeuNetUI),
      openDlg(new QFileDialog),
      createUi(new Ui::CreateNetUI), createDlg(new QDialog),

      addLimitsUi(new Ui::AddLimitsUI), addLimitsDlg(new QDialog),

      createValidator(new QRegExpValidator(QRegExp("([1-9]{1}[0-9]*,|[1-9]{1}[0-9]*-[1-9]{1}[0-9]*,)+"))),
      addSetUi(new Ui::AddSetUI), addSetDlg(new QDialog),
      addSetValidator(new QRegExpValidator(QRegExp("[A-Za-z ]+")))
{
    ui->setupUi(this);
    createUi->setupUi(createDlg);
    addSetUi->setupUi(addSetDlg);
    addLimitsUi->setupUi(addLimitsDlg);

    this->adjustUi();
    this->setWindowState(Qt::WindowMaximized);

    this->updateUI();
}

void NeuNetUI::adjustUi() {
    openDlg->setDirectory(DEFAULT_NETS_DIR);



    connect(ui->netCreate, SIGNAL(clicked()), SLOT(onCreateShow()));
    connect(createUi->ok, SIGNAL(clicked()), SLOT(onCreateNets()));
    connect(createUi->cancel, SIGNAL(clicked()), createDlg, SLOT(hide()));
    createUi->neurons->setValidator(createValidator);

    connect(ui->netLoad, SIGNAL(clicked()), openDlg, SLOT(show()));
    connect(openDlg, SIGNAL(filesSelected(QStringList)), SLOT(onLoadNets(QStringList)));
    connect(ui->netSave, SIGNAL(clicked()), SLOT(onSaveNets()));
    connect(ui->netRemove, SIGNAL(clicked()), SLOT(onRemoveNets()));

    connect(ui->dataAdd, SIGNAL(clicked()), SLOT(onAddShow()));
    connect(addSetUi->ok, SIGNAL(clicked()), SLOT(onAddData()));
    connect(addSetUi->cancel, SIGNAL(clicked()), addSetDlg, SLOT(hide()));
    addSetUi->dataSet->setValidator(addSetValidator);

    connect(ui->dataRefresh, SIGNAL(clicked()), SLOT(onRefreshData()));
    connect(ui->dataRemove, SIGNAL(clicked()), SLOT(onRemoveData()));
    connect(ui->dataCombine, SIGNAL(clicked()), SLOT(onCombineData()));

    connect(ui->tute, SIGNAL(clicked()), SLOT(onLimitsShow()));
//    connect(addLimitsUi->ok, )
    connect(ui->tute, SIGNAL(clicked()), SLOT(onTeachNets()));
}

NeuNetUI::~NeuNetUI() {
    delete ui;
    delete createDlg;
    delete addLimitsDlg;

    delete addLimitsUi;
    delete addLimitsValidator;
    delete createUi;
    delete createValidator;

    delete addSetUi;
    delete addSetDlg;
    delete addSetValidator;
}

 QTreeWidget * NeuNetUI::getDataView() const {
    return ui->data;
 }

 QTableWidget * NeuNetUI::getNetsView() const {
     return ui->nets;
 }
//-------------------------------------------------------------------------------------------------
void NeuNetUI::onShowInfo(QString info) {
    QMessageBox msgBox;
    msgBox.setText(info);
    msgBox.exec();
}

void NeuNetUI::onShowException(QString problem) {
    ui->messages->setText(problem);
}

void NeuNetUI::onShowDebug(QString msg) {
    ui->lstProcess->addItem(msg);
    ui->lstProcess->scrollToBottom();
}


void NeuNetUI::onLoadNets(QStringList files) {
    ui->messages->setText("");

    for (QString file : files)
        if (file.contains(".net")) {
            emit loadNet(file);
        } else {
            QMessageBox msgBox;
            msgBox.setText("You can only load .net files.");
            msgBox.exec();
        }
    emit updateNets(ui->nets);
}

void NeuNetUI::onSaveNets() {
    ui->messages->setText("");

    for (QTableWidgetItem * item : ui->nets->selectedItems())
        if (item->column() == 0)
            emit saveNet(item->text() + ".net", item->row());
}

void NeuNetUI::onRemoveNets() {
    ui->messages->setText("");

    QList<QTableWidgetItem *> items = ui->nets->selectedItems();

    for (int I = 0; I < items.size(); ++I)
        if (items[I] && items[I]->column() == 0) {
            emit removeNet(items[I]->row());
            ui->nets->removeRow(items[I]->row());
            items[I + 1] = NULL;
        }

    emit updateNets(ui->nets);
}


//-------------------------------------------------------------------------------------------------

void NeuNetUI::onLimitsShow()
{
    addLimitsDlg->show();
}

void NeuNetUI::onCreateShow() {
    createUi->name->setText("");
    createUi->layersCnt->setValue(1);
    createUi->neurons->setText("");
    createUi->ok->setFocus();
    createDlg->show();
}

void NeuNetUI::onCreateNets() {
    ui->messages->setText("");

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

            neuronsCnt.append(NeuronsCount(range_from, range_to));
        } else
            neuronsCnt.append(NeuronsCount(item.toInt()));
    }

    QString funcName = createUi->func->currentText();
    emit createNets(name, funcName, neuronsCnt);
    createDlg->hide();

    emit updateNets(ui->nets);
}
//-------------------------------------------------------------------------------------------------
void NeuNetUI::updateUI() {
    emit updateNets(ui->nets);
    emit updateData(ui->data);
}

void NeuNetUI::onTeachNets() {
    ui->messages->setText("");

    QList<QTableWidgetItem *> nets = ui->nets->selectedItems();
    Ints netIds;

    for (int I = 0; I < nets.size(); ++I)
        if (nets[I] && nets[I]->column() == 0)
            netIds.append(I);

    emit teachNets();
}
//-------------------------------------------------------------------------------------------------
void NeuNetUI::onAddShow() {
    addSetUi->overlay->setText("");
    addSetUi->ok->setFocus();
    addSetDlg->show();
}

void NeuNetUI::onAddData() {
    QString newName = addSetUi->dataSet->text();

    for (int I = 0; I < ui->data->topLevelItemCount(); ++I) {
        QTreeWidgetItem * ptwi = ui->data->topLevelItem(I);
        if (ptwi->childCount() != 0)
            if (ptwi->text(0) == newName) {
                addSetUi->overlay->setText("Name of set already exists");
                return;
            }
    }

    emit addData(newName);
    emit updateData(ui->data);
    addSetDlg->hide();
}

void NeuNetUI::onRemoveData() {
    // TODO: removing
    emit updateData(ui->data);
}

void NeuNetUI::onCombineData() {
    // TODO: combining
    emit updateData(ui->data);
}

void NeuNetUI::onRefreshData() {
    emit refreshData();
    emit updateData(ui->data);
}
//-------------------------------------------------------------------------------------------------

} // namespace NetManagers
