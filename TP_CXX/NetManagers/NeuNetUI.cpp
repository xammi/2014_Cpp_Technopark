#include "NeuNetUI.h"
#include "../NetTutors/TuteData.h"
#include "ui_neunetui.h"
#include "ui_createNet.h"
#include "ui_addLimits.h"

namespace NetManagers {

using NetTutors::TuteBoundaries;

const int PROCESS_TIMER_STEP = 500;
const int UI_NETS_PARAMS_CNT = 3;

const QString PROCESS_FILL_WELCOME = ">> Process: ";
const QString PROCESS_FILLER = "=";
const int PROCESS_FILLER_CNT = 14;

//-------------------------------------------------------------------------------------------------
NeuNetUI::NeuNetUI(QWidget *parent) :
      QMainWindow(parent), ui(NULL), openDlg(NULL), createUi(NULL), createDlg(NULL),createValidator(NULL),
      addLimitsUi(NULL), addLimitsDlg(NULL)
{
    this->setDefaultConf();

    ui->setupUi(this);
    createUi->setupUi(createDlg);
    addLimitsUi->setupUi(addLimitsDlg);

    this->adjustUi();
    this->setWindowState(Qt::WindowMaximized);

    updateUI(UPD::ALL);
}

void NeuNetUI::setDefaultConf() {
    try {
        ui = new Ui::NeuNetUI;
        openDlg = new QFileDialog;
        createUi = new Ui::CreateNetUI;
        createDlg = new QDialog;
        createValidator = new QRegExpValidator(QRegExp("([1-9]{1}[0-9]*,|[1-9]{1}[0-9]*-[1-9]{1}[0-9]*,)+"));
        addLimitsUi = new Ui::AddLimitsUI;
        addLimitsDlg = new QDialog;

    } catch (std::bad_alloc &) {
        this->~NeuNetUI();
        throw;
    }
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

    connect(ui->dataRefresh, SIGNAL(clicked()), SLOT(onRefreshData()));
    connect(ui->tute, SIGNAL(clicked()), SLOT(onLimitsShow()));

    connect(addLimitsUi->ok, SIGNAL(clicked()), SLOT(onTuteNets()));
    connect(addLimitsUi->cancel, SIGNAL(clicked()), addLimitsDlg, SLOT(hide()));

    connect(ui->test, SIGNAL(clicked()), SLOT(onTestNets()));
}

NeuNetUI::~NeuNetUI() {
    if (ui) delete ui;
    if (createDlg) delete createDlg;
    if (addLimitsDlg) delete addLimitsDlg;

    if (addLimitsUi) delete addLimitsUi;
    if (createUi) delete createUi;
    if (createValidator) delete createValidator;
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

    updateUI(UPD::NETS);
}

void NeuNetUI::onSaveNets() {
    ui->messages->setText("");

    for (QTableWidgetItem * item : ui->nets->selectedItems())
        if (item->column() == 0)
            emit saveNet(item->text() + ".net", item->row());

    updateUI(UPD::NETS);
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

    updateUI(UPD::NETS);
}


//-------------------------------------------------------------------------------------------------
void NeuNetUI::onLimitsShow() {
    if (ui->nets->selectedItems().size() > 0)
        if (ui->data->selectedItems().size() > 0)
            addLimitsDlg->show();
        else
            ui->messages->setText("Choose data for teaching");
    else
        ui->messages->setText("Choose nets for teaching");
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

    for (QTableWidgetItem * item : ui->nets->selectedItems())
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
    for (QString item : nDataList) {
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

    updateUI(UPD::NETS);
}
//-------------------------------------------------------------------------------------------------
void NeuNetUI::updateUI(UPD upd) {
    if (upd == UPD::DATA || upd == UPD::ALL) {
        emit updateData(ui->data);
    }
    if (upd == UPD::NETS || upd == UPD::ALL) {
        emit updateNets(ui->nets);
        for (Index index : tuteNow)
            for (int I = 0; I < UI_NETS_PARAMS_CNT; ++I)
                ui->nets->item(index, I)->setBackgroundColor(Qt::yellow);
    }
}

void NeuNetUI::selectedNets(Ints & netIds) const {
    netIds.clear();

    for (QTableWidgetItem *item : ui->nets->selectedItems())
        if (item && tuteNow.contains(item->row()))
            throw AlreadyTute();

    for (QTableWidgetItem *item : ui->nets->selectedItems()) {
        if (item && item->column() == 0) {
            int index = item->row();
            netIds.append(index);
        }
        item->setSelected(false);
    }
}

void NeuNetUI::onTestNets() {
    ui->messages->setText("");

    Ints netIds;
    try {
        selectedNets(netIds);
    } catch (Exception &exc) {
        onShowException(exc.toString());
    }

    QStringList keySet;
    for (QTreeWidgetItem * item : ui->data->selectedItems()) {

        if (item->parent()) {
            QString parentText;
            parentText = item->parent()->text(0);
            keySet.append(parentText + '/' + item->text(0));
        }
        else {
            keySet.append(item->text(0));
        }

        if (item->childCount() != 0) {
            ui->messages->setText("Folders are not permitted");
            return;
        }

        item->setSelected(false);
    }

    emit testNets(netIds, keySet);
    updateUI(UPD::NETS);
}

void NeuNetUI::onTuteNets() {
    ui->messages->setText("");

    Ints netIds;
    try {
        selectedNets(netIds);
    } catch (Exception &exc) {
        onShowException(exc.toString());
    }

    QStringList keySet;
    for (QTreeWidgetItem * item : ui->data->selectedItems()) {
        keySet.append(item->text(0));

        if (item->childCount() == 0) {
            ui->messages->setText("Only folders are permitted");

            addLimitsDlg->hide();
            return;
        }

        item->setSelected(false);
    }

    TuteBoundaries tutitionLimits( addLimitsUi->netError->value(), addLimitsUi->layerError->value()
                                    , addLimitsUi->netIter->value(), addLimitsUi->layerIter->value()
                                    , addLimitsUi->speed->value() );

    addLimitsDlg->hide();
    emit tuteNets(netIds, keySet, tutitionLimits);
    updateUI(UPD::NETS);
}

void NeuNetUI::onRefreshData() {
    emit refreshData();
    updateUI(UPD::DATA);
}

void NeuNetUI::onRequestUpdate() {
    this->onRefreshData();
    updateUI(UPD::ALL);
}
//-------------------------------------------------------------------------------------------------
void NeuNetUI::onTuteStarted(int index) {

    if (tuteNow.isEmpty()) {
        processTimer = startTimer(PROCESS_TIMER_STEP);
        ui->process->setText(PROCESS_FILL_WELCOME);
    }

    tuteNow.insert(index);
    onShowDebug("Started tute for: " + QString::number(index));
    updateUI(UPD::NETS);
}

void NeuNetUI::onTuteFinished(int index) {

    tuteNow.remove(index);
    onShowDebug("Tute successfully finished: " + QString::number(index));

    if (tuteNow.isEmpty()) {
        killTimer(processTimer);
        ui->process->setText("");
    }
    updateUI(UPD::NETS);
}

void NeuNetUI::timerEvent(QTimerEvent *event) {
    if (event->timerId() == processTimer) {
        static int counter = 0;

        if (counter == PROCESS_FILLER_CNT) {
            counter = 0;
            ui->process->setText(PROCESS_FILL_WELCOME);
        }

        ui->process->setText(ui->process->text() + PROCESS_FILLER);
        counter++;
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace NetManagers
