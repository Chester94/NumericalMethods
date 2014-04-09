#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

#include <qwt_symbol.h>

#include <QToolButton>
#include <QHBoxLayout>
#include <qwt_counter.h>

#include "difference.h"
#include "derivativefx.h"
#include "derivativepx.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    QwtPlotGrid *grid;
    QwtPlotMagnifier *magnifier;
    QwtPlotPanner *d_panner;

    Function *fx;
    Polynomial *px;
    Difference *rx;
    DerivativeFx *dfx;
    DerivativePx *dpx;


    QwtPlotCurve *curve_fx,
                 *curve_px,
                 *curve_rx,
                 *curve_dfx,
                 *curve_dpx,
                 *pointMaxDif;


    void setPlot();
    void setPlotGrid();
    void enableMagnifier();
    void enableMovingOnPlot();

    void createCurves();

    void set_curve_fx();
    void set_curve_px();
    void set_curve_rx();
    void set_curve_dfx();
    void set_curve_dpx();

    void set_point_MaxDif();

    void setCurveParameters(QwtPlotCurve *curve, QString title, QColor color, int width);

private slots:
    void on_applySetting_clicked();
    void on_fx_clicked(bool checked);
    void on_px_clicked(bool checked);
    void on_rx_clicked(bool checked);
    void on_dfx_clicked(bool checked);
    void on_dpx_clicked(bool checked);
    void on_maxDif_clicked(bool checked);
};

#endif // MAINWINDOW_H
