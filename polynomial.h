#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <qmath.h>

#include "function.h"

class Polynomial
{
private:
    double fx0;
    double xb;
    double xe;
    double x0;
    double h;

    int n;

    double *delta;

    //double fx0m(int m);
    double ratio(double t, int m, double &oldFactor);

    double* deltaValue(Function &func);

public:
    Polynomial();
    Polynomial(double _xb, double _xe, int _n, Function &func);

    double value(double x);
};

#endif // POLYNOMIAL_H
