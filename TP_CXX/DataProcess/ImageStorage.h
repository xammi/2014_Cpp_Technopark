#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include <QMap>
#include <QPixmap>
#include <QStringList>
#include <QDir>

#include "AbstractStorage.h"
#include "PtrVector.h"

namespace DataProcess {

const QString DEFAULT_CATALOG = "/image_data/";

typedef QMap <QString, QPixmap *> ImageMap;
typedef QString StrKey;
typedef uint NumKey;
//-------------------------------------------------------------------------------------------------
class ImageSet : Containable
{
public:
    ImageSet(const QString &);
    ~ImageSet();

    const QString & name() const { return this->setName; }

    void append(const StrKey &);
    QPixmap remove(const NumKey);
    QPixmap remove(const StrKey &);
    void clear() throw ();

    QPixmap & operator () (const StrKey &);

private:
    QString setName;
    ImageMap imgs;
};

//-------------------------------------------------------------------------------------------------
typedef PtrVector<ImageSet> ImageSets;
const int NO_KEY = -1;

class ImageStorage : public AbstractStorage {
    Q_OBJECT

public:
    ImageStorage(const QString & dir = DEFAULT_CATALOG);
    ~ImageStorage();

    ImageSet & operator() (const StrKey &);

    ImageSet & createSet(const QString &);
    void deleteSet(const StrKey &);

    void fillSet(const StrKey & whereSet, const QStringList & imgKeys);

private:
    Index findSet(const StrKey &) const;

    const QString catalog;
    ImageSets sets;
};
//-------------------------------------------------------------------------------------------------
struct UnknownSetKey : public Exception {
    QString toString() { return "Неизвестный ключ множества"; }
};

struct UnknownImgKey : public Exception {
    QString toString() { return "Неизвестный ключ картинки"; }
};

struct DirNotCreated : public Exception {
    QString toString() { return "Не получилось создать директорию для ImageSet"; }
};

struct NotUniqueKey : public Exception {
    QString toString() { return "Передан не уникальный ключ"; }
};

//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // IMAGESTORAGE_H
