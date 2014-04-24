#ifndef NETFUNCTION_H
#define NETFUNCTION_H

#include "includes.h"

#define _REG_(command, str) \
registri(new Func([] (double X) { \
    return command; \
}, str)) \
//-------------------------------------------------------------------------------------------------
typedef std::function<double (double)> T_Func;

class Func
{
public:
    Func(T_Func _func, QString str)
        : func(_func), _name(str) {}

    double operator ()(double X) const { return func(X); }
    const QString & name() const { return _name; }

private:
    T_Func func;
    QString _name;
};

typedef QVector<Func *> Funcs;
//-------------------------------------------------------------------------------------------------
class FuncDisp
{
public:
    static Func * func(const QString & str);

private:
    FuncDisp() {
        _REG_(X*X*X, "x^3");
        _REG_(X*X, "x^2");
        _REG_(sqrt(X), "SQRT(x)");
        _REG_(sin(X), "SIN(x)");
        _REG_(cos(X) - X, "COS(x) - x");
    }

    ~FuncDisp();

    void registri(Func *);
    Func * get_func(const QString & name) const;

    static FuncDisp * instance;
    Funcs funcs;
};
//-------------------------------------------------------------------------------------------------


#endif // NETFUNCTION_H