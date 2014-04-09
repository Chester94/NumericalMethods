#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <qmath.h>

#include "function.h"

class Polynomial : public QwtSyntheticPointData
{
private:
    double fx0;
    double startPoint;
    double endPoint;
    double x0;
    double h;

    int n;

    double *delta;

    //double fx0m(int m);
    double ratio(double t, int m, double &oldFactor) const;

    double* deltaValue(Function *func);

    void calculateValues(Function *func);

public:
    /*Polynomial();
    Polynomial(double _xb, double _xe, int _n, Function &func);*/

    Polynomial(Function *func,
               const double _startPoint = 0.0, const double _endPoint = 1.0,
               const double _n = 11.0)
            : QwtSyntheticPointData(100), startPoint(_startPoint), endPoint(_endPoint),
              n(_n)
    {
        calculateValues(func);
    }

    void setParametrs(Function *func,
                      const double _startPoint, const double _endPoint, const double _n);

    double value(double x) const;

    virtual double y(double x) const
    {
        return value(x);
    }
};

#endif // POLYNOMIAL_H
