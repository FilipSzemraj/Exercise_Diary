#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

namespace Ui {
class chart;
}

class chart : public QDialog
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr, QLineSeries *series = nullptr, int x = 0, int max=0);
    ~chart();

private:
    Ui::chart *ui;

    QLineSeries *actSeries;
    int howMany;
    int maxVolume;
};

#endif // CHART_H
