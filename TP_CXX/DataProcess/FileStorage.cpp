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
    for (QDir & dir : folders) {
        ptwi = new QTreeWidgetItem(treeView);
        ptwi->setText(0, dir.dirName());

        QTreeWidgetItem * twi_file;
        for (QString file : dir.entryList(QDir::Files)) {
            twi_file = new QTreeWidgetItem(ptwi);
            twi_file->setText(0, file);
        }
    }
}
//-------------------------------------------------------------------------------------------------
QDir & FileStorage::findDir(const StrKey & folder) {
    for (QDir & dir : folders)
        if (dir.dirName() == folder)
            return dir;
    throw UnknownStrKey();
}

void FileStorage::loadDirs(QList<InputDataSet> & data, const QStringList &keys) {
    if (processor == NULL)
        throw ImgProcessorNotFound();

    InputDataSet inputSet;

    for (QString key : keys) {
        inputSet.clear();
        loadDir(inputSet, key);
        data.append(inputSet);
    }
}

int FileStorage::loadDir(InputDataSet & inputSet, const StrKey & folder) {
    if (processor == NULL)
        throw ImgProcessorNotFound();

    QDir & dir = findDir(folder);

    for (QString file : dir.entryList(QDir::Files)) {
        InputData *input = new InputData;
        QString filepath = dir.absoluteFilePath(file);

        loadFile(*input, file, filepath);
        inputSet.append(input);
    }

    return dir.entryList(QDir::Files).size();
}
//-------------------------------------------------------------------------------------------------
void FileStorage::loadFiles(InputDataSet & inputSet, const QStringList & keys) {
    for (QString key : keys) {

        QStringList parts = key.split('/');
        QDir & dir = findDir(parts[0]);
        QString filepath;

        InputData *input = new InputData;

        if (parts.size() == 2) {
            filepath = dir.absoluteFilePath(parts[1]);
            loadFile(*input, parts[1], filepath);

        } else if (parts.size() == 1) {
            filepath = QDir(catalog).absoluteFilePath(key);
            loadFile(*input, key, filepath);
        }

        inputSet.append(input);
    }
}

void FileStorage::loadFile(InputData & input, const QString & file, const QString & filepath) {
    QImage image;
    QString text;

    if (file.contains(".png")) {
        loadImage(image, filepath);
        processor->processData(input, image);

    } else if (file.contains(".txt") || ! file.contains(".")) {
        loadText(text, filepath);
        processor->processTxt(input, text);
    }
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
