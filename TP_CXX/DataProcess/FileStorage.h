#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include <QDir>
#include <QTreeWidget>

#include "includes.h"
#include "ImageProcessor.h"

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
    FileStorage(ImageProcessor *, const QString & dir = DEFAULT_CATALOG);

    QDir & findDir(const StrKey &);

    void loadFiles(InputDataSet &, const QStringList & keys);
    void loadFile(InputData &, const QString &, const QString &);

    void loadDirs(QList<InputDataSet> &, const QStringList & keys);
    int loadDir(InputDataSet &, const StrKey &);

private:
    void loadImage(QImage &, const StrKey &);
    void loadText(QString &, const StrKey &);

private:
    const QString catalog;
    QVector<QDir> folders;
    ImageProcessor *processor;
};
//-------------------------------------------------------------------------------------------------
struct ImgProcessorNotFound : public Exception {
    QString toString() { return "Процессор картинок не задан"; }
};

struct NotUniqueKey : public Exception {
    QString toString() { return "Передан не уникальный ключ"; }
};

struct OpenFileError : public Exception {
    QString toString() { return "Не удалось открыть файл"; }
};

struct UnknownStrKey : public Exception {
    QString toString() { return "Неизвестный строковый ключ"; }
};

//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGESTORAGE_H
