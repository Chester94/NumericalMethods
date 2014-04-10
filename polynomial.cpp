#include "polynomial.h"

double Polynomial::ratio(double t, int m, double &oldFactor) const
{
    oldFactor /= m;

    if( m % 2 )
        return oldFactor;
    else
    {
        double tmp = oldFactor;
        oldFactor *= (t*t - qPow(m/2, 2));
        return tmp*t;
    }
}

double *Polynomial::deltaValue(Function *func)
{
    double **deltaTable;
    int i, j;

    deltaTable = new double* [2*n-1];

    for( i = 0; i < 2*n-1; i++ )
        deltaTable[i] = new double [n];

    for( i = 0; i < 2*n-1; i++)
        for( j = 0; j < n; j++)
            deltaTable[i][j] = 0;

    for( i = -(n-1); i <= n-1; i++ )
        deltaTable[i + (n-1)][0] = func->value(x0 + i*h/2);

    for( i = 1; i < n; i++ )
        for( j = i; j < 2*n-1-i; j++ )
            deltaTable[j][i] = deltaTable[j+1][i-1] - deltaTable[j-1][i-1];

    double *tmp = deltaTable[n-1];

    for( i = 0; i < n-1; i++ )
        delete deltaTable[i];

    for( i = n; i < 2*n-1; i++ )
        delete deltaTable[i];

    delete deltaTable;

    return tmp;
}

void Polynomial::calculateValues(Function *func)
{
    x0 = (startPoint + endPoint) / 2;

    fx0 = func->value(x0);

    if(n != 1)
        h = (endPoint - startPoint) / (n-1);
    else
        h = 0;

    if(delta)
        delete delta;

    delta = deltaValue(func);
}

double Polynomial::value(double x) const
{
    double t = (x - x0) / h;
    double oldFactor = t;

    double val = fx0;

    for( int i = 1; i < n ; i++ )
        val += ratio(t, i, oldFactor)*delta[i];

    return val;
}

void Polynomial::setParametrs(Function *func,
                              const double _startPoint = 0.0, const double _endPoint = 1.0,
                              const double _n = 11.0)
{
    startPoint = _startPoint;
    endPoint = _endPoint;
    n = _n;

    calculateValues(func);
}
