#include "TuteModule.h"
#include <QThread>

namespace NetTutors {
//-------------------------------------------------------------------------------------------------
TuteModule::TuteModule() {
}

TuteModule::~TuteModule() {
    if (tutor) delete tutor;
    if (tester) delete tester;
}

void TuteModule::run() {
    if (tester == NULL || tutor == NULL) {
        emit toException(TuteModuleExc::NotConfigured().toString());
        return;
    }

    try {
        emit toDebug(" Обучение началось: " + net->name());
        tutor->start(ttdata);
    }
    catch (Exception & exc) {
        emit toException(exc.toString());
    }

    emit finished();
}
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors
