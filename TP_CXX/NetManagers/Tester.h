#ifndef TESTER_H
#define TESTER_H

#include "../includes.h"

namespace NetManagers {

//-------------------------------------------------------------------------------------------------
class Tester : public QObject {
    Q_OBJECT
public:
    Tester();
    CompRes test(TuteData data);
private:
    AbstractNet* NeuNet;
};
//-------------------------------------------------------------------------------------------------
} // namespace Tester
#endif // TESTER_H
