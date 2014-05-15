#ifndef ABSTRACTSTORAGE_H
#define ABSTRACTSTORAGE_H

#include "../includes.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
struct AbstractStorage : public QObject {
    virtual ~AbstractStorage() {}
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess
#endif // ABSTRACTSTORAGE_H
