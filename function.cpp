#include "function.h"

Function::Function()
{
    alpha = betta = delta = epsil = 0;
}

Function::Function(qreal _alpha, qreal _betta, qreal _delta, qreal _epsil)
{
    alpha = _alpha;
    betta = _betta;
    delta = _delta;
    epsil = _epsil;
}

void Function::setParameters(qreal _alpha, qreal _betta, qreal _delta, qreal _epsil)
{
    alpha = _alpha;
    betta = _betta;
    delta = _delta;
    epsil = _epsil;
}

qreal Function::value(qreal x)
{
    qreal tmp = epsil * sin( delta * x );

    if( betta * x == 0 )
        return 1 + tmp;

    if( alpha*alpha - x*x*x == 0 )
        return 0 + tmp;

    return cos( betta * x / ( alpha*alpha - x*x*x ) ) + tmp;
}
