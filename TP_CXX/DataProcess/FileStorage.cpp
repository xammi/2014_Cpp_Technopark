#include "FileStorage.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
FileStorage::FileStorage(ImageProcessor *proc, const QString &dir)
    :   catalog(dir), processor(proc)
{
    if (processor == NULL)
        throw ImgProcessorNotFound();

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
QDir & FileStorage::findDir(const StrKey & folder) {
    for (QDir & dir : folders)
        if (dir.dirName() == folder)
            return dir;
    throw UnknownStrKey();
}

void FileStorage::load(QList<InputDataSet> & data, const QStringList &keys) {
    if (processor == NULL)
        throw ImgProcessorNotFound();

    InputDataSet inputSet;

    for (QString key : keys) {
        inputSet.clear();
        load(inputSet, key);
        data.append(inputSet);
    }
}

int FileStorage::load(InputDataSet & inputSet, const StrKey & folder) {
    if (processor == NULL)
        throw ImgProcessorNotFound();

    QDir & dir = findDir(folder);
    QImage image;
    QString text;

    for (QString file : dir.entryList(QDir::Files)) {
        InputData *input = new InputData;
        QString filepath = dir.absoluteFilePath(file);

        if (file.contains(".png")) {
            loadImage(image, filepath);
            processor->processData(*input, image);

        } else if (file.contains(".txt") || ! file.contains(".")) {
            loadText(text, filepath);
            processor->processTxt(*input, text);
        }

        inputSet.append(input);
    }

    return dir.entryList(QDir::Files).size();
}

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
