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

    double countInterpolationNodes = 3;
    double h = (endPoint - startPoint) / (countInterpolationNodes - 1);

    Function f(1, 0, 1, 1);
    Polynomial p(&f, startPoint, endPoint, countInterpolationNodes);

    double x = startPoint;
    int i = 0;

    while(x < endPoint)
    {
        qDebug() << ++i << x << f.value(x) << p.value(x);
        x += 0.05;
    }*/

    return a.exec();
}
