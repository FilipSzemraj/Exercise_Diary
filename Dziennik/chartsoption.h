#ifndef CHARTSOPTION_H
#define CHARTSOPTION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>
#include "ranking.h"
#include "chart.h"


namespace Ui {
class chartsOption;
}

class chartsOption : public QDialog
{
    Q_OBJECT

    QSqlDatabase *mydb;

public:
    explicit chartsOption(QWidget *parent = nullptr, QSqlDatabase *db = nullptr, int id = 0);
    ~chartsOption();

private slots:
    void on_chartB_clicked();

    void on_ranking_clicked();

    void on_GroupEx_CB_textActivated(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::chartsOption *ui;

    int id;
    chart *chartWindow;
    ranking *rankingWindow;
    QString repairDate(QDate temp);
    void fillComboBox();
    QSqlQuery qry;
    bool filling;
};

#endif // CHARTSOPTION_H
