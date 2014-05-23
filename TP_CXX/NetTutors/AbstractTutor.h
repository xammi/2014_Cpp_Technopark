#ifndef ABSTRACTTUTOR_H
#define ABSTRACTTUTOR_H

#include "../includes.h"
#include "TuteData.h"

#include "AbstractTutor.h"
#include "../NetManagers/Tester.h"

namespace NetTutors {

using NetManagers::Tester;
using NeuNets::AbstractNet;

//-------------------------------------------------------------------------------------------------
class AbstractTutor : public QObject {
    Q_OBJECT

public:
    virtual ~AbstractTutor() {}
    virtual void initialize() = 0;
    virtual bool start(const TuteData &) = 0;

    virtual void setNet(AbstractNet *) = 0;
    virtual void setTester(Tester *) = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors

#endif // ABSTRACTTUTOR_H
