#ifndef RANKING_H
#define RANKING_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>

namespace Ui {
class ranking;
}

class ranking : public QDialog
{
    Q_OBJECT

    QSqlDatabase *mydb;

public:
    explicit ranking(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~ranking();

private slots:
    void on_ExitB_clicked();

private:
    Ui::ranking *ui;

    void fillTable();
    QSqlQuery qry;
    bool filling;
};

#endif // RANKING_H
