#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <qmath.h>

#include "function.h"

class Polynomial
{
private:
    qreal fx0;
    qreal xb;
    qreal xe;
    qreal x0;
    qreal h;

    int n;

    qreal *delta;

    //qreal fx0m(int m);
    qreal ratio(qreal t, int m, qreal &oldFactor);

    qreal* deltaValue(Function &func);

public:
    Polynomial();
    Polynomial(qreal _xb, qreal _xe, int _n, Function &func);

    qreal value(qreal x);
};

#endif // POLYNOMIAL_H
