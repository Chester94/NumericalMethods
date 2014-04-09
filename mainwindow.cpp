#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создать поле со шкалами для отображения графика
    setPlot();

    // Включить масштабную сетку
    setPlotGrid();

    // Включить возможность приближения/удаления графика
    enableMagnifier();

    // Включить возможность перемещения по графику
    enableMovingOnPlot();

    fx = new Function(ui->alpha->value(), ui->betta->value(),
                      ui->delta->value(), ui->epsil->value());

    px = new Polynomial(fx, ui->A->value(), ui->B->value(), ui->n->value()*2 + 1);

    createCurves();

    set_curve_fx();
    set_curve_px();

    ui->drawingArea->replot();
}

MainWindow::~MainWindow()
{
    if(grid)
        delete grid;

    if(magnifier)
        delete magnifier;

    if(d_panner)
        delete d_panner;


    if(curve_fx)
        delete curve_fx;

    if(curve_px)
        delete curve_px;

    if(curve_rx)
        delete curve_rx;

    if(curve_dfx)
        delete curve_dfx;

    if(curve_dpx)
        delete curve_dpx;

    delete ui;
}

void MainWindow::setPlot()
{
    ui->drawingArea->setTitle( "Сюда вписать функцию" ); // заголовок
    ui->drawingArea->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    ui->drawingArea->setAxisTitle(QwtPlot::xBottom, "X");
    ui->drawingArea->setAxisTitle(QwtPlot::yLeft, "Y");
    ui->drawingArea->insertLegend( new QwtLegend() );
    ui->drawingArea->setAxisScale(QwtPlot::xBottom,
                                  ui->A->value(), ui->B->value()); // задавать минимум и максимум осей
    ui->drawingArea->setAxisScale(QwtPlot::yLeft,
                                  ui->C->value(), ui->D->value());
}

void MainWindow::setPlotGrid()
{
    grid = new QwtPlotGrid();
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach(ui->drawingArea); // добавить сетку к полю графика
}

void MainWindow::enableMagnifier()
{
    magnifier = new QwtPlotMagnifier( ui->drawingArea->canvas() );
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
}

void MainWindow::enableMovingOnPlot()
{
    d_panner = new QwtPlotPanner( ui->drawingArea->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::LeftButton );
}

void MainWindow::createCurves()
{
    curve_fx = new QwtPlotCurve();
    curve_px = new QwtPlotCurve();
    curve_rx = new QwtPlotCurve();
    curve_dfx = new QwtPlotCurve();
    curve_dpx = new QwtPlotCurve();
}

void MainWindow::set_curve_fx()
{
    setCurveParameters(curve_fx, "f(x)", Qt::blue, 1);
    curve_fx->attach(ui->drawingArea);
    curve_fx->setData(fx);

    curve_fx->setVisible(ui->fx->isChecked());
}

void MainWindow::set_curve_px()
{
    setCurveParameters(curve_px, "P(x)", Qt::red, 1);
    curve_px->attach(ui->drawingArea);
    curve_px->setData(px);

    curve_px->setVisible(ui->px->isChecked());
}

void MainWindow::setCurveParameters(QwtPlotCurve *curve, QString title, QColor color, int width)
{
    curve->setTitle(title);
    curve->setPen(color, width); // цвет и толщина кривой
    curve->setRenderHint
        ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
}

/*void MainWindow::on_draw_clicked()
{
    if (flag)
        curve->detach();
    flag = true;

    getParametersWindow();
    ui->qwt_widget->setAxisScale(QwtPlot::xBottom, a, b); // задавать минимум и максимум осей
    ui->qwt_widget->setAxisScale(QwtPlot::yLeft, c, d);

    // Кривая
    if(ui->fx->isChecked()){
        setCurveParameters();
        addPointsToCurveAndShow();
    }


    //setCurveParameters();
    test();


    ui->qwt_widget->replot(); // перерисовать

}*/

/*void MainWindow::test()
{
    if(curve)
        delete curve;

    curve = new QwtPlotCurve();

    getParametersFunction();

    curve->setTitle( "f(x)" );
    curve->setPen( Qt::blue, 1 ); // цвет и толщина кривой
    curve->setRenderHint
        ( QwtPlotItem::RenderAntialiased, true ); // сглаживание

    curve->attach(ui->qwt_widget);
    curve->setData(new Function(alpha, betta, gamma, epsilon));
    qDebug() << alpha << betta << gamma << epsilon;
}*/

void MainWindow::on_applySetting_clicked()
{
    ui->drawingArea->setAxisScale(QwtPlot::xBottom,
                                 ui->A->value(), ui->B->value()); // задавать минимум и максимум осей
    ui->drawingArea->setAxisScale(QwtPlot::yLeft,
                                 ui->C->value(), ui->D->value());

    fx->setParameters(ui->alpha->value(), ui->betta->value(),
                      ui->delta->value(), ui->epsil->value());
    px->setParametrs(fx, ui->A->value(), ui->B->value(), ui->n->value()*2 + 1);

    ui->drawingArea->replot();
}

void MainWindow::on_fx_clicked(bool checked)
{
    curve_fx->setVisible(checked);
    ui->drawingArea->replot();
}

void MainWindow::on_px_clicked(bool checked)
{
    curve_px->setVisible(checked);
    ui->drawingArea->replot();
}
