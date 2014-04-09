#ifndef DERIVATIVEPX_H
#define DERIVATIVEPX_H

#include "polynomial.h"

class DerivativePx : public QwtSyntheticPointData
{
private:
    Polynomial *poly;
    double delta;

public:
    DerivativePx(Polynomial *_poly, const double _delta = 1.0)
            : QwtSyntheticPointData(100), poly(_poly), delta(_delta)
    {
    }

    void setDelta(double _delta) {delta = _delta;}

    virtual double y(double x) const
    {
        return (poly->value(x+delta) - poly->value(x)) / delta;
    }
};

#endif // DERIVATIVEPX_H
