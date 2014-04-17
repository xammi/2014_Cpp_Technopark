#include "ImageStorage.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
ImageStorage::ImageStorage(const QString & dir)
    :   catalog(dir)
{}

ImageStorage::~ImageStorage()
{}
//-------------------------------------------------------------------------------------------------
Index ImageStorage::findSet(const StrKey & key) const {
    for (Index I = 0; I < sets.size(); ++I)
        if (sets[I]->name() == key)
            return I;

    return NO_KEY;
}

ImageSet & ImageStorage::operator() (const StrKey & key) {
    for (Index I = 0; I < sets.size(); ++I)
        if (sets[I]->name() == key)
            return *sets[I];

    throw UnknownSetKey();
}

ImageSet & ImageStorage::createSet(const QString & newName) {
    if (findSet(newName) == NO_KEY)
        throw NotUniqueKey();

    QDir curDir;

    bool isDirMade = curDir.mkdir(newName);
    if (! isDirMade)
        throw DirNotCreated();

    ImageSet *newSet = new ImageSet(newName);
    sets.append(newSet);

    return *sets.last();
}

void ImageStorage::deleteSet(const StrKey & key) {
    Index pos = findSet(key);
    if (pos == NO_KEY)
        throw UnknownSetKey();

    sets[pos]->clear();
    sets.remove(pos);
}

void ImageStorage::fillSet(const StrKey & whereSet, const QStringList & imgKeys) {
}
//-------------------------------------------------------------------------------------------------
ImageSet::ImageSet(const QString & _name)
    :   setName(_name) {}

ImageSet::~ImageSet() {}

void ImageSet::clear() throw () {
    imgs.clear();
}

//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
