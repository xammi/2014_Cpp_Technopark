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
    static Func & func(const QString & str);

private:
    FuncDisp() {
//        _REG_((1 / (1 + exp(-1 * X))), "Sigmoid");
        /*
         *Важный момент.
         *При увеличении размеров картинки получается очень большое
         *значение Х. Чтобы продолжать иметь хороший порог, нужно менять
         *коэффициент альфа (в предыдущем случае = 1)
         *_REG_((1 / (1 + exp(-0.01 * X))), "Sigmoid"); - good for big nets
         */
        _REG_((1 / (1 + exp(-1 * X))), "Sigmoid");
        _REG_((1 / (1 + exp(-0.1 * X))), "Sigmoid_0.1");
        _REG_((1 / (1 + exp(-0.01 * X))), "Sigmoid_0.01");
        _REG_((tanh(X / 1)), "HypTan");
    }

    ~FuncDisp();

    void registri(Func *);
    Func * get_func(const QString & name) const;

    static FuncDisp * instance;
    Funcs funcs;
};
//-------------------------------------------------------------------------------------------------

#endif // NETFUNCTION_H
