#include "mainwindow.h"
#include <QApplication>

#include "function.h"
#include "polynomial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*double startPoint = 0;
    double endPoint = 1;

    double countInterpolationNodes = 75;
    double h = (endPoint - startPoint) / (countInterpolationNodes - 1);

    Function f(1, 0, 1, 1);
    Polynomial p(startPoint, endPoint, countInterpolationNodes, f);

    double x = startPoint;
    int i = 0;

    while(i != countInterpolationNodes)
    {
        qDebug() << ++i << x << f.value(x) << p.value(x);
        x += h;
    }*/

    return a.exec();
}
