#include "FileStorage.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
FileStorage::FileStorage(const QString &dir)
    :   catalog(dir)
{
    this->onRefreshData();
}

void FileStorage::onRefreshData() {
    folders.clear();

    QDir qdir(catalog);
    QStringList listFiles = qdir.entryList(QDir::Dirs);

    for (QString inDir : listFiles) {
        if (inDir == "." || inDir == "..")
            continue;
        folders.append(QDir(catalog + inDir));
    }
}
//-------------------------------------------------------------------------------------------------
void FileStorage::onUpdate(QTreeWidget *treeView) {
    treeView->clear();

    QTreeWidgetItem * ptwi;
    for (int I = 0; I < folders.count(); ++I) {
        ptwi = new QTreeWidgetItem(treeView);
        ptwi->setText(0, folders[I].dirName());
    }
}
//-------------------------------------------------------------------------------------------------
void FileStorage::loadImage(QImage & img, const StrKey & str) {
    img.load(str);
}

void FileStorage::loadText(QString & target, const StrKey & path) {
    QFile file(path);
    if (! file.open(QIODevice::ReadOnly))
        throw OpenFileError();

    QTextStream in(& file);
    target = in.readAll();
}
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
