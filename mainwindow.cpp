#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(double _a, double _b, double _c, double _d, double _n, double _alpha, double _betta, double _epsilon, double _gamma)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;

    n = _n;

    alpha = _alpha;
    betta = _betta;
    gamma = _gamma;
    epsilon = _epsilon;

}

void MainWindow::getParametersWindow()
{
    a = ui->A->value();
    b = ui->B->value();
    c = ui->C->value();
    d = ui->D->value();
}

void MainWindow::getParametersFunction()
{
    alpha = ui->alpha->value();
    betta = ui->betta->value();
    gamma = ui->gamma->value();
    epsilon = ui->epsilon->value();
}

void MainWindow::getParametersNode()
{
    n = ui->n->value();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Создать поле со шкалами для отображения графика
    setPlot();

    // Включить масштабную сетку
    setPlotGrid();

    // Кривая
    setCurveParameters();
    addPointsToCurveAndShow();

    // Включить возможность приближения/удаления графика
    enableMagnifier();

    // Включить возможность перемещения по графику
    enableMovingOnPlot();

    connect(ui->draw, SIGNAL(clicked()), SLOT(draw()));
}

void MainWindow::setPlot(){

    //setCentralWidget(ui->qwt_widget); // привязать поле к границам окна

    ui->qwt_widget->setTitle( "Сюда вписать функцию" ); // заголовок
    ui->qwt_widget->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    ui->qwt_widget->setAxisTitle(QwtPlot::yLeft, "Y");
    ui->qwt_widget->setAxisTitle(QwtPlot::xBottom, "X");
    ui->qwt_widget->insertLegend( new QwtLegend() );
    ui->qwt_widget->setAxisScale(QwtPlot::xBottom, -100, 100); // задавать минимум и максимум осей
    ui->qwt_widget->setAxisScale(QwtPlot::yLeft, -100, 100);
}

void MainWindow::setPlotGrid(){

    grid = new QwtPlotGrid();
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach(ui->qwt_widget); // добавить сетку к полю графика

}

void MainWindow::setCurveParameters()
{
    curve = new QwtPlotCurve();
    curve->setTitle( "f(x)" );
    curve->setPen( Qt::blue, 6 ); // цвет и толщина кривой
    curve->setRenderHint
        ( QwtPlotItem::RenderAntialiased, true ); // сглаживание

    // Маркеры кривой
    symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );
}


void MainWindow::addPointsToCurveAndShow()
{

    // Добавить точки на ранее созданную кривую
    // Значения точек записываются в массив, затем считываются
    // из этого массива
    for (int i = 0; i < 5; i++) {
        pointArray[i][0] = 1.0 + 0.5*i;
        pointArray[i][1] = 1.0 + 0.5*i;

        points << QPointF( pointArray[i][0], pointArray[i][1]);
    }

    curve->setSamples( points ); // ассоциировать набор точек с кривой

    curve->attach( ui->qwt_widget ); // отобразить кривую на графике
}

void MainWindow::enableMagnifier()
{

    magnifier = new QwtPlotMagnifier(ui->qwt_widget->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
}

void MainWindow::enableMovingOnPlot()
{

    d_panner = new QwtPlotPanner( ui->qwt_widget->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
}

void MainWindow::draw()
{
    getParametersWindow();
    ui->qwt_widget->setAxisScale(QwtPlot::xBottom, a, b); // задавать минимум и максимум осей
    ui->qwt_widget->setAxisScale(QwtPlot::yLeft, c, d);

    ui->qwt_widget->replot(); // перерисовать
}


MainWindow::~MainWindow()
{
    delete ui;
}
