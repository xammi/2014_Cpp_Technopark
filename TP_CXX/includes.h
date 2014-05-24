#ifndef INCLUDES_H
#define INCLUDES_H
//-------------------------------------------------------------------------------------------------
#include <QDebug>
#include <qmath.h>

#include <QVector>
#include <QString>
#include <QStringList>
#include <QDialog>

#include <QObject>
#include <QPixmap>

#include <functional>

using std::function;
using std::pair;

struct Exception {
    virtual QString toString() = 0;
};

typedef QVector<int> Ints;
typedef int Index;
typedef const Index CIndex;
//-------------------------------------------------------------------------------------------------
#endif // INCLUDES_H
