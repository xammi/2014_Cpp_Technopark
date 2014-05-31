#ifndef TUTEMODULE_H
#define TUTEMODULE_H

#include <QRunnable>

#include "../NeuNet/AbstractNet.h"
#include "AbstractTutor.h"
#include "../NetManagers/Tester.h"

namespace NetTutors {

using NeuNets::AbstractNet;
using NetManagers::Tester;

//-------------------------------------------------------------------------------------------------
class TuteModule : public QObject, public QRunnable
{
    Q_OBJECT

signals:
    void toException(QString);
    void toDebug(QString);
    void finished();

public:
    TuteModule();

    virtual ~TuteModule();

    template <class Tutor>
    void configure(AbstractNet *, const TuteData &, const TuteBoundaries &);

    void run();

private:
    AbstractNet *net;

    Tester * tester;
    AbstractTutor * tutor;
    TuteData ttdata;
};
//-------------------------------------------------------------------------------------------------
namespace TuteModuleExc {

struct NetNotFound : public Exception {
    QString toString() { return QString("Сеть не найдена на этапе TuteModule"); }
};

struct NotConfigured : public Exception {
    QString toString() { return QString("TuteModule не был сконфигурирован"); }
};

}
//-------------------------------------------------------------------------------------------------
// implementation of configure template

template <class Tutor>
void TuteModule::configure(AbstractNet *_net, const TuteData & data, const TuteBoundaries & boundaries) {
    if (! net)
        throw TuteModuleExc::NetNotFound();

    net = _net;
    ttdata = data;

    try {
        tester = new Tester;
        tutor = new Tutor;

        tester->setTarget(net);
        tutor->setTester(tester);
        tutor->setNet(net);
        tutor->setLimits(boundaries);

        connect(tester, SIGNAL(toDebug(QString)), this, SIGNAL(toDebug(QString)));
        connect(tutor, SIGNAL(toDebug(QString)), this, SIGNAL(toDebug(QString)));
    }
    catch (Exception &) {
        this->~TuteModule();
        throw;
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace NetTutors
#endif // TUTEMODULE_H
