#include "FileStorage.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
FileStorage::FileStorage(const QString &dir)
    :   catalog(dir), uppers("")
{
    this->onRefreshData();
}

void FileStorage::onRefreshData() {
    uppers.clear();
    sets.clear();

    QDir qdir(catalog);
    QStringList listFiles = qdir.entryList(QDir::Files);
    for (QString file : listFiles)
        uppers.append(file, qdir.absoluteFilePath(file));

    QStringList listDir = qdir.entryList(QDir::Dirs);
    for (QString inDir : listDir) {
        if (inDir == "." || inDir == "..") continue;

        sets.append(new PathSet(inDir));

        QDir qInDir(catalog + inDir);
        for (QString file : qInDir.entryList(QDir::Files))
            sets.last()->append(file, qInDir.absoluteFilePath(file));
    }
}

FileStorage::~FileStorage()
{}
//-------------------------------------------------------------------------------------------------
Index FileStorage::findSet(const StrKey &key) const {
    for (Index I = 0; I < sets.size(); ++I)
        if (sets[I]->name() == key)
            return I;

    return NO_KEY;
}

PathSet & FileStorage::operator() (const StrKey &key) {
    for (Index I = 0; I < sets.size(); ++I)
        if (sets[I]->name() == key)
            return *sets[I];

    throw UnknownSetKey();
}

PathSet & FileStorage::createSet(const QString &newName) {
    if (findSet(newName) != NO_KEY)
        throw NotUniqueKey();

    QDir curDir(catalog);

    bool isDirMade = curDir.mkdir(newName);
    if (! isDirMade)
        throw DirNotCreated();

    PathSet *newSet = new PathSet(newName);
    sets.append(newSet);

    return *sets.last();
}

void FileStorage::deleteSet(const StrKey &key) {
    Index pos = findSet(key);
    if (pos == NO_KEY)
        throw UnknownSetKey();

    QDir curDir(catalog);
    bool isDirDeleted = curDir.rmdir(key);
    if (! isDirDeleted)
        throw DirNotDeleted();

    sets[pos]->clear();
    sets.remove(pos);
}

void FileStorage::onUpdate(QTreeWidget *treeView) {
    treeView->clear();

    QTreeWidgetItem * ptwi;
    for (int I = 0; I < uppers.count(); ++I) {
        ptwi = new QTreeWidgetItem(treeView);
        ptwi->setText(0, uppers.key(I));
    }

    for (PathSet * set : sets) {
        QTreeWidgetItem * set_wi = new QTreeWidgetItem(treeView);
        set_wi->setText(0, set->name());

        for (int I = 0; I < set->count(); ++I) {
            ptwi = new QTreeWidgetItem(set_wi);
            ptwi->setText(0, set->key(I));
        }
    }
    treeView->expandAll();
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
