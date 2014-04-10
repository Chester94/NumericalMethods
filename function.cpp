#include "function.h"

void Function::setParameters(double _alpha, double _betta, double _delta, double _epsil)
{
    alpha = _alpha;
    betta = _betta;
    delta = _delta;
    epsil = _epsil;
}

double Function::value(double x) const
{
    double tmp = epsil * sin( delta * x );

    if( betta * x == 0 )
        return 1 + tmp;

    if( alpha*alpha - x*x*x == 0 )
        return 0.5 + tmp;

    return cos( betta * x / ( alpha*alpha - x*x*x ) ) + tmp;
}
