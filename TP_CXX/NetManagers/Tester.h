#ifndef TESTER_H
#define TESTER_H

#include "../includes.h"
#include "../NeuNet/abstrnet.h"
#include "../NetTutors/TutitionData.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
class Tester : public QObject {
    Q_OBJECT
public:
    Tester();
    CompResult test(TuteData data);
private:
    NeuNets::AbstrNet *net;
};
//-------------------------------------------------------------------------------------------------
} // namespace Tester
#endif // TESTER_H
