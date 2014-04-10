#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include "../includes.h"

namespace DataProcess {
struct Image{};
struct InputData{};
//-------------------------------------------------------------------------------------------------
class AbstractProcessor : public QObject {
    Q_OBJECT

public:
private:
    virtual void binarize() = 0;
    virtual void segment() = 0;
    virtual void crop() = 0;
    virtual void resize() = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
