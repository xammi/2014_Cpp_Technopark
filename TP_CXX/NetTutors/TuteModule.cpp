#include "TuteModule.h"
#include <QThread>

namespace NetTutors {
//-------------------------------------------------------------------------------------------------
TuteModule::TuteModule(CIndex _index)
    :   index(_index)
{}

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
        emit started(index);

        // teaching of net here
        tutor->start(ttdata);

        emit finished(index);
    }
    catch (Exception & exc) {
        emit toException(exc.toString());
    }
}
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors
