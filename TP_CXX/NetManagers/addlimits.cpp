#include "addlimits.h"
#include "ui_addLimits.h"

AddLimits::AddLimits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLimitsUI)
{
    ui->setupUi(this);
}

AddLimits::~AddLimits()
{
    delete ui;
}
