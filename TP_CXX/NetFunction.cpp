#include "NetFunction.h"

FuncDisp * FuncDisp::instance = 0;

Func & FuncDisp::func(const QString & str) {
    if (! instance)
        instance = new FuncDisp;

    return *instance->get_func(str);
}

FuncDisp::~FuncDisp() {
    for (int I = 0; I < funcs.size(); ++I)
        delete funcs[I];
}

void FuncDisp::registri(Func * func) { funcs.append(func); }

Func * FuncDisp::get_func(const QString & name) const {
    for (int I = 0; I < funcs.size(); ++I)
        if (name.contains(funcs[I]->name()))
            return funcs[I];

    qDebug() << "Не найдена функция, соответствующая " << name;
    return NULL;
}
//-------------------------------------------------------------------------------------------------
