#ifndef FUNCTION_H
#define FUNCTION_H

#include <qmath.h>

#include <qwt_point_data.h>

#include <QDebug>

class Function : public QwtSyntheticPointData
{
private:
    double alpha;
    double betta;
    double delta; // gamma
    double epsil;

public:
    //Function();
    //Function(double _alpha, double _betta, double _delta, double _epsil);

    Function(const double &_alpha = 1.0, const double &_betta = 0.0,
             const double &_delta = 1.0, const double &_epsil = 1.0)
            : QwtSyntheticPointData(100), alpha(_alpha), betta(_betta), delta(_delta), epsil(_epsil)
    {
    }

    void setParameters(double _alpha, double _betta, double _delta, double _epsil);

    double value(double x) const;

    virtual double y(double x) const
    {
        return value(x);
    }
};

#endif // FUNCTION_H
