#include "TuteModule.h"

namespace NetTutors {
//-------------------------------------------------------------------------------------------------
template <class Tutor>
TuteModule::TuteModule(AbstractNet *net) {
    if (! net)
        emit toException("Сеть не найдена на этапе TuteModule");

    this->configure<Tutor>(net);
}

template <class Tutor>
TuteModule::TuteModule(AbstractNet *net, const TuteData &_data, const TuteBoundaries &bounds) :
    ttdata(_data)
{
    if (! net)
        emit toException("Сеть не найдена на этапе TuteModule");

    this->configure<Tutor>(net);
    tutor->setLimits(bounds);
}

template <class Tutor>
void TuteModule::configure(AbstractNet *net) {
    try {
        tester = new Tester;
        tutor = new Tutor;

        tutor->setTester(tester);
        tester->setTarget(net);
        tutor->setNet(net);

        connect(tester, SIGNAL(toDebug(QString)), SLOT(toDebug(QString)));
        connect(tutor, SIGNAL(toDebug(QString)), SLOT(toDebug(QString)));
    }
    catch (Exception & exc) {
        this->~TuteModule();
        emit toException(exc.toString());
    }
}

TuteModule::~TuteModule() {
    if (tutor) delete tutor;
    if (tester) delete tester;
}

void TuteModule::run() {
    try {
        tutor->start(ttdata);
    } catch (Exception & exc) {
        emit toException(exc.toString());
    }

    emit finished();
}
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors
