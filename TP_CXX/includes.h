#ifndef INCLUDES_H
#define INCLUDES_H
//-------------------------------------------------------------------------------------------------
#include <QDebug>
#include <qmath.h>

#include <QVector>
#include <QString>
#include <QDialog>

#include <QObject>
#include <QPixmap>

#include <functional>

using std::function;

struct Exception {
    virtual QString toString() = 0;
};
//-------------------------------------------------------------------------------------------------
#endif // INCLUDES_H
