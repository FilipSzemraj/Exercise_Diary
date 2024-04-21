#include "chart.h"
#include "ui_chart.h"

chart::chart(QWidget *parent, QLineSeries *series, int x, int max) :
    QDialog(parent),
    actSeries(series),
    howMany(x),
    maxVolume(max),
    ui(new Ui::chart)
{
    ui->setupUi(this);

    QChart *chart = new QChart();
    chart->addSeries(actSeries);
    chart->legend()->hide();
    chart->setTitle("Wykres pokazujacy ilosc powtorzen pomnozona razy ciezar.");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(howMany);
    axisX->setFormat("dd.MM.yyyy");
    axisX->setTitleText("Data");
    chart->addAxis(axisX, Qt::AlignBottom);
    actSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Suma dzwiganego ciezaru");
    axisY->setMin(0);
    axisY->setRange(0, maxVolume+500);
    chart->addAxis(axisY, Qt::AlignLeft);
    actSeries->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QMainWindow window;
    chartView->setParent(ui->horizontalFrame);
    //chartView->

}

chart::~chart()
{
    delete ui;
}
