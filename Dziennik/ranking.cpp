#include "ranking.h"
#include "ui_ranking.h"

ranking::ranking(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    mydb(db),
    ui(new Ui::ranking)
{
    ui->setupUi(this);

    mydb->open();
    filling=false;
    fillTable();
}

ranking::~ranking()
{
    delete ui;
}

void ranking::on_ExitB_clicked()
{
    close();
}

void ranking::fillTable()
{
    if(filling)
    {
        return;
    }
    filling = true;
    qry.prepare("SELECT count(max) FROM (SELECT max(etd.weight) max "
                "FROM exercise_training_day etd "
                "JOIN exercises_set es ON es.id_exercise = etd.id_exercise "
                "JOIN training_day td ON td.id_training_day = etd.id_training_day "
                "JOIN user u ON u.id_user = td.id_user "
                "GROUP BY es.name);");
    qry.exec();
    qry.first();
    ui->tableWidget->setRowCount(qry.value(0).toInt());

    qry.prepare("SELECT max(etd.weight), etd.reps, es.name, td.d, u.name, u.surname "
                "FROM exercise_training_day etd "
                "JOIN exercises_set es ON es.id_exercise = etd.id_exercise "
                "JOIN training_day td ON td.id_training_day = etd.id_training_day "
                "JOIN user u ON u.id_user = td.id_user "
                "GROUP BY es.name;");

    if(qry.exec())
    {
        int row=0;
        for(qry.first(); qry.isValid(); qry.next(), ++row)
        {
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(qry.value(0).toString()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(qry.value(1).toString()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(qry.value(2).toString()));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(qry.value(3).toString()));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(qry.value(4).toString()));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(qry.value(5).toString()));
        }
    }

    filling = false;
}

