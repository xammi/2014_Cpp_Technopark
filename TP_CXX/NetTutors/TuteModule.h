#ifndef TUTEMODULE_H
#define TUTEMODULE_H

#include <QRunnable>

#include "../NeuNet/AbstractNet.h"
#include "AbstractTutor.h"
#include "../NetManagers/Tester.h"

namespace NetTutors {

using NeuNets::AbstractNet;
using namespace NetTutors;
using NetManagers::Tester;

//-------------------------------------------------------------------------------------------------
class TuteModule : public QRunnable
{
    Q_OBJECT

signals:
    void toException(QString);
    void toDebug(QString);
    void finished();

public:
    template <class Tutor>
    TuteModule(AbstractNet *);

    template <class Tutor>
    TuteModule(AbstractNet *, const TuteData &, const TuteBoundaries &);

    virtual ~TuteModule();

    void run();

private:
    template <class Tutor>
    void configure(AbstractNet *);

    Tester * tester;
    AbstractTutor * tutor;
    TuteData ttdata;
};
//-------------------------------------------------------------------------------------------------

} // namespace NetTutors
#endif // TUTEMODULE_H
