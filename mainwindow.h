#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

#include <QToolButton>
#include <QHBoxLayout>
#include <qwt_counter.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    double a;
    double b;
    double c;
    double d;

    double alpha;
    double betta;
    double gamma; // delta
    double epsilon;

    int n;


    MainWindow(double _a, double _b, double _c, double _d, double _n,
               double _alpha, double _betta, double _epsilon, double _gamma);

    void getParametersWindow(); // a, b, c, d
    void getParametersFunction(); // alpha, betta ...
    void getParametersNode();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;



    void setPlot();

    QwtPlotGrid *grid;
    void setPlotGrid();

    QwtPlotCurve *curve;
    QwtSymbol *symbol;

    void setCurveParameters();

    // новый массив точек кривой
    double pointArray[5][2];
    QPolygonF points;
    void addPointsToCurveAndShow();

    QwtPlotMagnifier *magnifier;
    void enableMagnifier();


    QwtPlotPanner *d_panner;
    void enableMovingOnPlot();


private slots:
    void on_draw_clicked();
};

#endif // MAINWINDOW_H
