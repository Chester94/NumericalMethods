#include "polynomial.h"

/*Polynomial::Polynomial()
{
}

Polynomial::Polynomial(double _xb, double _xe, int _n, Function &func)
{
    xb = _xb;
    xe = _xe;
    x0 = (xe + xb) / 2;

    n = _n;

    fx0 = func.value(x0);
    h = (xe - xb) / (n-1);

    delta = deltaValue(func);

    for( int j = 0; j < n; j++)
        qDebug() << delta[j];
}*/

/*double Polynomial::fx0m(int m)
{
    if( m == 1)
        return func.value(x+h/2) - func.value(x-h/2);
    else
        return fx0m(x+h/2, m-1) - fx0m(x-h/2, m-1);

    return delta[m][(n-m)/2];
}*/

double Polynomial::ratio(double t, int m, double &oldFactor) const
{
    /*int count_numerator_multipliers = 0;
    int count_denominator_multipliers = 0;

    double rat = t;
    count_numerator_multipliers++;

    if( m % 2 == 0 )
    {
        rat *= t;
        count_numerator_multipliers++;
    }

    while( (count_numerator_multipliers != (m/2 + 1)) &&
           (count_denominator_multipliers != m) )
    {

    }*/

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
    /*for(int i = 0; i < n+1; i++)
        for(int j = 0; j < n+1; j++)
            delta[i][j] = 0;

    for(int i = 0; i < n+1; i++)
    {
        for(int j = 0; j < n+1; j++)
            qDebug() << delta[i][j];
        qDebug() << "******";
    }*/

    /*for(int i = -n/2; i <= n/2; i++)
    {
        delta[0][i+n/2] = func.value(x0+i*h/2);
        //qDebug() << func.value(x0+i*h/2);
    }

    for(int i = 1; i < n; i++)
        for(int j = 0; j < n-i; j++)
            delta[i][j] = delta[i-1][j+1] - delta[i-1][j];

    /*for(int i = 0; i < n+1; i++)
    {
        for(int j = 0; j < n+1; j++)
            qDebug() << delta[i][j];
        qDebug() << "******";
    }*/

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

    /*qDebug() << deltaTable[n-1][0] << deltaTable[n-1-2][0] << deltaTable[n-1+2][0];
    qDebug() << func.value(x0) << func.value(x0-h) << func.value(x0+h);*/

    for( i = 1; i < n; i++ )
        for( j = i; j < 2*n-1-i; j++ )
            deltaTable[j][i] = deltaTable[j+1][i-1] - deltaTable[j-1][i-1];

    //qDebug() << deltaTable[n-1][1] << deltaTable[n-1-1][1] << deltaTable[n-1+1][1];

    /*for( i = 0; i < 2*n-1; i++)
    {
        for( j = 0; j < n; j++)
            qDebug() << deltaTable[i][j];
        qDebug() << "******" << i << "******";
    }*/

    /*for( j = 0; j < n; j++ )
    {
        for( i = 0; i < 2*n-1; i++ )
            qDebug() << deltaTable[i][j];
        qDebug() << "******" << j << "******";
    }*/

    /*for( j = 0; j < n; j++)
        qDebug() << deltaTable[n-1][j];*/

    /*for( i = 0; i < 2*n-1; i++ )
        qDebug() << i << deltaTable[i][50];*/

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
    {
        //qDebug() << oldFactor;
        val += ratio(t, i, oldFactor)*delta[i];
    }

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
