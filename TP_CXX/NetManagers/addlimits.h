#ifndef ADDLIMITS_H
#define ADDLIMITS_H

#include <QDialog>

namespace Ui {
class AddLimitsUI;
}

class AddLimits : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddLimits(QWidget *parent = 0);
    ~AddLimits();
    
private:
    Ui::AddLimitsUI *ui;
};

#endif // ADDLIMITS_H
