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
    rx = new Difference(fx, px);

    dfx = new DerivativeFx(fx, ui->deltaForDerivative->value());

    dpx = new DerivativePx(px, ui->deltaForDerivative->value());

    createCurves();

    set_curve_fx();
    set_curve_px();
    set_curve_rx();
    set_curve_dfx();
    set_curve_dpx();

    set_point_MaxDif();

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

    if(pointMaxDif)
        delete pointMaxDif;

    delete ui;
}

void MainWindow::setPlot()
{
    ui->drawingArea->setTitle( "cos( ßx / (ɑ^2 - x^3) ) + ɛsin( δx )" ); // заголовок
    ui->drawingArea->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    ui->drawingArea->setAxisTitle(QwtPlot::xBottom, "X");
    ui->drawingArea->setAxisTitle(QwtPlot::yLeft, "Y");
    ui->drawingArea->insertLegend( new QwtLegend(), QwtPlot::BottomLegend );
    ui->drawingArea->setAxisScale(QwtPlot::xBottom,
                                  ui->A->value(), ui->B->value());
    // задавать минимум и максимум осей
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

    pointMaxDif = new QwtPlotCurve();
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

void MainWindow::set_curve_rx()
{
    setCurveParameters(curve_rx, "r(x)", Qt::cyan, 1);
    curve_rx->attach(ui->drawingArea);
    curve_rx->setData(rx);

    curve_rx->setVisible(ui->rx->isChecked());
}

void MainWindow::set_curve_dfx()
{
    setCurveParameters(curve_dfx, "df(x)", Qt::green, 1);
    curve_dfx->attach(ui->drawingArea);
    curve_dfx->setData(dfx);

    curve_dfx->setVisible(ui->dfx->isChecked());
}

void MainWindow::set_curve_dpx()
{
    setCurveParameters(curve_dpx, "dp(x)", Qt::magenta, 1);
    curve_dpx->attach(ui->drawingArea);
    curve_dpx->setData(dpx);

    curve_dpx->setVisible(ui->dpx->isChecked());
}

void MainWindow::set_point_MaxDif()
{
    setCurveParameters(pointMaxDif, "maxDif", Qt::yellow, 1);

    double begin = ui->A->value();
    double end = ui->B->value();

    double h = (end - begin) / 1000;

    double x = begin;
    double maxDif_x = begin;

    while(x < end)
    {
        if( rx->y(x) > rx->y(maxDif_x) )
            maxDif_x = x;

        x += h;
    }

    double y = fx->value(maxDif_x);

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
            QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    pointMaxDif->setSymbol( symbol );

    QPolygonF points;

    points << QPointF( maxDif_x, y ) ;

    pointMaxDif->setSamples( points ); // ассоциировать набор точек с кривой

    pointMaxDif->attach( ui->drawingArea ); // отобразить кривую на графике

    pointMaxDif->setVisible(ui->maxDif->isChecked());
}

void MainWindow::setCurveParameters(QwtPlotCurve *curve, QString title, QColor color, int width)
{
    curve->setTitle(title);
    curve->setPen(color, width); // цвет и толщина кривой
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    // сглаживание
}

void MainWindow::on_applySetting_clicked()
{
    if( ui->A->value() >= ui->B->value() || ui->C->value() >= ui->D->value() )
    {
        QMessageBox *errorMessage = new QMessageBox(QMessageBox::Critical,
                                                    "Error", "Check window parametrs");
        errorMessage->exec();
        delete errorMessage;
        return;
    }

    if(ui->centerCheck->isChecked())
    {
        ui->drawingArea->setAxisScale(QwtPlot::xBottom,
                                      ui->A->value(), ui->B->value());
        // задавать минимум и максимум осей
        ui->drawingArea->setAxisScale(QwtPlot::yLeft,
                                      ui->C->value(), ui->D->value());
    }

    fx->setParameters(ui->alpha->value(), ui->betta->value(),
                      ui->delta->value(), ui->epsil->value());
    px->setParametrs(fx, ui->A->value(), ui->B->value(), ui->n->value()*2 + 1);

    dfx->setDelta(ui->deltaForDerivative->value());

    set_point_MaxDif();

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

void MainWindow::on_rx_clicked(bool checked)
{
    curve_rx->setVisible(checked);
    ui->drawingArea->replot();
}

void MainWindow::on_dfx_clicked(bool checked)
{
    curve_dfx->setVisible(checked);
    ui->drawingArea->replot();
}

void MainWindow::on_dpx_clicked(bool checked)
{
    curve_dpx->setVisible(checked);
    ui->drawingArea->replot();
}

void MainWindow::on_maxDif_clicked(bool checked)
{
    pointMaxDif->setVisible(checked);
    ui->drawingArea->replot();
}
