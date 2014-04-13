#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include "InputData.h"
#include "OutputData.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
struct AbstractProcessor : public QObject {

    virtual InputData * prepareData(QPixmap &) = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
