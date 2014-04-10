#ifndef BACKPROPTUTOR_H
#define BACKPROPTUTOR_H

#include "AbstractTutor.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------
class BackPropTutor : public AbstractTutor {
    Q_OBJECT
public:
    BackPropTutor();
    void initialize();
    bool start(QVector <TuteData> &Data);
private:
    double propagate(); // EG What??
    void backPropagate();
};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors
#endif // BACKPROPTUTOR_H
