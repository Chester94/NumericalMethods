#include "mainwindow.h"
#include <QApplication>

#include "function.h"
#include "polynomial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qreal startPoint = 0;
    qreal endPoint = 1;

    qreal countInterpolationNodes = 75;
    qreal h = (endPoint - startPoint) / (countInterpolationNodes - 1);

    Function f(1, 0, 1, 1);
    Polynomial p(startPoint, endPoint, countInterpolationNodes, f);

    qreal x = startPoint;
    int i = 0;

    while(i != countInterpolationNodes)
    {
        qDebug() << ++i << x << f.value(x) << p.value(x);
        x += h;
    }

    return a.exec();
}
