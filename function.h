#ifndef FUNCTION_H
#define FUNCTION_H

#include <qmath.h>

#include <QDebug>

class Function
{
private:
    qreal alpha;
    qreal betta;
    qreal delta; // gamma
    qreal epsil;

public:
    Function();
    Function(qreal _alpha, qreal _betta, qreal _delta, qreal _epsil);

    void setParameters(qreal _alpha, qreal _betta, qreal _delta, qreal _epsil);

    qreal value(qreal x);
};

#endif // FUNCTION_H
