#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "polynomial.h"

class Difference : public QwtSyntheticPointData
{
private:
    Function *func;
    Polynomial * poly;

public:
    Difference(Function *_func, Polynomial *_poly)
            : QwtSyntheticPointData(100), func(_func), poly(_poly)
    {
    }

    virtual double y(double x) const
    {
        double r = func->value(x) - poly->value(x);
        return r > 0 ? r : -r;
    }
};

#endif // DIFFERENCE_H
