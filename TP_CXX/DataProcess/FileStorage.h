#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include <QDir>
#include <QTreeWidget>

#include "includes.h"
#include "PtrVector.h"

namespace DataProcess {

const QString DEFAULT_CATALOG = "../TP_CXX/Default store/";

typedef int Index;
typedef QString StrKey;

//-------------------------------------------------------------------------------------------------
class FileStorage : public QObject {
    Q_OBJECT

public slots:
    void onRefreshData();
    void onUpdate(QTreeWidget *);

public:
    FileStorage(const QString & dir = DEFAULT_CATALOG);

    void load(const StrKey & folder);
    void loadImage(QImage &, const StrKey &);
    void loadText(QString &, const StrKey &);

private:
    const QString catalog;
    QVector<QDir> folders;
};
//-------------------------------------------------------------------------------------------------
struct NotUniqueKey : public Exception {
    QString toString() { return "Передан не уникальный ключ"; }
};

struct OpenFileError : public Exception {
    QString toString() { return "Не удалось открыть файл"; }
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGESTORAGE_H
