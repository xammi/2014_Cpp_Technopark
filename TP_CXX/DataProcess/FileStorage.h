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
typedef int NumKey;
const int NO_KEY = -1;

//-------------------------------------------------------------------------------------------------
struct IndexOutOfRange : public Exception {
    QString toString() { return "Индекс вне границ массива на этапе NamedSet"; }
};

struct UnknownItemKey : public Exception {
    QString toString() { return "Неизвестный ключ на этапе выборки из NamedSet"; }
};
//-------------------------------------------------------------------------------------------------
template <typename Type, class UnknownKey>
class NamedSet
{
public:
    NamedSet(const QString &_name) : setName(_name) {}
    ~NamedSet() {}

    const QString & name() const { return this->setName; }

    bool isEmpty() const { return (keys.size() == 0); }

    void clear () {
        keys.clear();
        items.clear();
    }

    void append(const StrKey &key, const Type &item) {
        keys.append(key);
        items.append(item);
    }

    Type remove(const NumKey index) {
        Type result = items[index];
        items.remove(index);
        keys.remove(index);
    }

    NumKey find(const StrKey &key) const {
        for (Index I = 0; I < keys.size(); ++I)
            if (keys[I] == key)
                return I;

        return NO_KEY;
    }

    Type remove(const StrKey &key) {
        NumKey index = find(key);
        if (index != NO_KEY)
            return this->remove(index);
        else
            throw UnknownKey();
    }

    Type & operator [] (const StrKey &key) {
        NumKey index = find(key);
        if (index != NO_KEY)
            return items[index];
        else
            throw UnknownKey();
    }

    Type & item (const NumKey index) {
        if (index < 0 || index > items.size())
            throw IndexOutOfRange();
        return items[index];
    }

    Type & key (const NumKey index) {
        if (index < 0 || index > keys.size())
            throw IndexOutOfRange();
        return keys[index];
    }

    int count() const { return keys.size(); }

private:
    QString setName;
    QVector<Type> items;
    QVector<StrKey> keys;
};

typedef QString PathToFile;
typedef NamedSet<PathToFile, UnknownItemKey> PathSet;
//-------------------------------------------------------------------------------------------------
typedef PtrVector<PathSet> PathSets;

class FileStorage : public QObject {
    Q_OBJECT

public slots:
    void onRefreshData();
    void onUpdate(QTreeWidget *);

public:
    FileStorage(const QString & dir = DEFAULT_CATALOG);
    virtual ~FileStorage();

    PathSet & operator() (const QString &);

    PathSet & createSet(const QString &);
    void deleteSet(const StrKey &);

    template <class FileLoader>
    bool loadItem(FileLoader &, const StrKey &);

private:
    Index findSet(const StrKey &) const;

    const QString catalog;
    PathSets sets;
    PathSet uppers;
};
//-------------------------------------------------------------------------------------------------
template <typename Goal>
struct FileLoader {
    FileLoader(Goal &_goal) : goal(_goal)  {}

    virtual void load(const QString &) = 0;

    Goal &goal;
};

struct ImageLoader : public FileLoader<QImage> {
    ImageLoader(QImage &_goal) : FileLoader(_goal)  {}

    void load(const QString &path) {
        this->goal.load(path);
    }
};

struct TextLoader : public FileLoader<QString> {
    TextLoader(QString &_goal) : FileLoader(_goal)  {}

    void load(const QString &);
};
//-------------------------------------------------------------------------------------------------
struct UnknownSetKey : public Exception {
    QString toString() { return "Неизвестный ключ множества"; }
};

struct DirNotCreated : public Exception {
    QString toString() { return "Не получилось создать директорию на этапе FileStorage"; }
};

struct DirNotDeleted : public Exception {
    QString toString() { return "Не получилось удалить директорию на этапе FileStorage"; }
};

struct NotUniqueKey : public Exception {
    QString toString() { return "Передан не уникальный ключ"; }
};

struct OpenFileError : public Exception {
    QString toString() { return "Не удалось открыть файл"; }
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGESTORAGE_H
