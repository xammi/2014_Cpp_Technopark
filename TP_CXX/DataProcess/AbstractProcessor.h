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
    virtual void binarize();
    virtual void segment();
    virtual void crop();
    virtual void resize();
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
