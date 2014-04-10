#ifndef ABSTRACTTUTOR_H
#define ABSTRACTTUTOR_H

#include "../includes.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------
class AbstractTutor : public QObject {
    Q_OBJECT

public:
    virtual void initialize();
    virtual bool start(QVector <TuteData> &Data);
private:
    virtual double propagate(); // EG What??
    virtual void backPropagate();
};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors

#endif // ABSTRACTTUTOR_H
