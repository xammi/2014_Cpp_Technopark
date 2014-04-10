#ifndef ABSTRACTTUTOR_H
#define ABSTRACTTUTOR_H

#include "../includes.h"

namespace NetTutors {

//-------------------------------------------------------------------------------------------------
class AbstractTutor : public QObject {
    Q_OBJECT

public:
    virtual void initialize() = 0;
    //virtual bool start(QVector <TuteData> &Data);
private:
    virtual double propagate() = 0; // EG What??
    virtual void backPropagate() = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetTutors

#endif // ABSTRACTTUTOR_H
