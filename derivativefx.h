#ifndef DERIVATIVEFX_H
#define DERIVATIVEFX_H

#include "function.h"

class DerivativeFx : public QwtSyntheticPointData
{
private:
    Function *func;
    double delta;

public:
    DerivativeFx(Function *_func, const double _delta = 1.0)
            : QwtSyntheticPointData(100), func(_func), delta(_delta)
    {
    }

    void setDelta(double _delta) {delta = _delta;}

    virtual double y(double x) const
    {
        return (func->value(x+delta) - func->value(x)) / delta;
    }
};

#endif // DERIVATIVEFX_H
