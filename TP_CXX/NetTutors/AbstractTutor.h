#ifndef ABSTRACTTUTOR_H
#define ABSTRACTTUTOR_H

#include "../includes.h"
#include "TutitionData.h"

namespace NetTutors {


//-------------------------------------------------------------------------------------------------
class AbstractTutor : public QObject {
    Q_OBJECT

public:
    virtual ~AbstractTutor() {}
    virtual void initialize() = 0;
    virtual bool start(const TuteData &) = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors

#endif // ABSTRACTTUTOR_H
