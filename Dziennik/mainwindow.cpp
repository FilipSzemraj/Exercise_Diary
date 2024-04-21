#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adding_exercise.h"
#include "calendar.h"
#include <QCalendarWidget>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QDate>

MainWindow::MainWindow(QWidget *parent, QSqlDatabase db, QString n, QString s)
    : QWidget(parent),
    mydbP(db),
    name(n),
    surname(s),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mydb=&mydbP;
    mydb->open();
    ui->Imie_L->setText(name);
    ui->Nazwisko_L->setText(surname);

    qry.prepare("SELECT id_user FROM user WHERE name=:n AND surname=:s;");
    qry.bindValue(":n", name);
    qry.bindValue(":s", surname);
    qry.exec();
    qry.next();
    id = qry.value(0).toInt();

    filling=false;
    trainingDate.setDate(2023,01,01);
    ui->DateB->setText("2023-01-01");
    fillForm();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CommitB_clicked()
{
    if(filling)
    {
        return;
    }
    filling = true;

    //Usuwanie danych z bazy

    QString date = ui->DateB->text();
    date.replace(" ", "-");
    QString idS = QString("%1").arg(id);
    qry.prepare("DELETE FROM exercise_training_day "
                "WHERE id_training_day=(SELECT td.id_training_day FROM training_day td "
                "JOIN exercise_training_day etd ON etd.id_training_day = td.id_training_day "
                "WHERE id_user=:i AND d=:d);");
    qry.bindValue(":i", idS);
    qry.bindValue(":d", date);
    qry.exec();

    qry.prepare("DELETE FROM training_day "
                "WHERE id_user=:i AND d=:d;");
    qry.bindValue(":i", idS);
    qry.bindValue(":d", date);
    qry.exec();


    //--------------------------
    //Dodawanie rekordow do bazy pobranych z aplikacji
    qry.prepare("INSERT INTO training_day(id_user, d) VALUES "
                "(:i, :d);");
    qry.bindValue(":i", idS);
    qry.bindValue(":d", date);
    qry.exec();

    qry.prepare("SELECT id_training_day FROM training_day "
                "WHERE id_user=:i AND d=:d;");
    qry.bindValue(":i", idS);
    qry.bindValue(":d", date);
    qry.exec();

    qry.next();
    QString trainingDay=qry.value(0).toString();

    int maxRow = ui->tableWidget->rowCount();

    for(int i=0;i<maxRow;i++)
    {
    QString name = ui->tableWidget->item(i, 0)->text();
    QString reps = ui->tableWidget->item(i, 1)->text();
    QString weight = ui->tableWidget->item(i, 2)->text();

    qry.prepare("INSERT INTO exercise_training_day (id_exercise, id_training_day, reps, weight) "
                "SELECT es.id_exercise, :td, :r, :w "
                "FROM exercises_set es "
                "WHERE name=:n;");
    qry.bindValue(":td", trainingDay);
    qry.bindValue(":r", reps);
    qry.bindValue(":w", weight);
    qry.bindValue(":n", name);
    qry.exec();


    }

    filling = false;

    fillForm();
}


void MainWindow::on_Add_B_clicked()
{
    windowExercise = new adding_exercise(this, mydb);
    windowExercise->setModal(true);
    windowExercise->show();
    connect(windowExercise, SIGNAL(sendDateForm(int, double ,QString, QString)), this, SLOT(receiveDateForm(int, double ,QString, QString)));
}

void MainWindow::receiveDate(QDate d)
{
int day = d.day();
int month = d.month();
int year = d.year();
trainingDate.setDate(year,month,day);

//Zamiana daty na taka z 0 na poczatku, jesli dzien lub miesiac jest 1 cyfrowy.
QString temp = repairDate();

ui->DateB->setText(temp);
fillForm();

}

void MainWindow::receiveDateForm(int reps, double weight, QString group, QString name)
{
    QString repsS = QString("%1").arg(reps);
    QString weightS = QString("%1").arg(weight);

    int maxRow = ui->tableWidget->rowCount();
    maxRow++;
    ui->tableWidget->setRowCount(maxRow);
    maxRow--;
    ui->tableWidget->setItem(maxRow, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(maxRow, 1, new QTableWidgetItem(repsS));
    ui->tableWidget->setItem(maxRow, 2, new QTableWidgetItem(weightS));
    ui->tableWidget->setItem(maxRow, 3, new QTableWidgetItem(group));
}

void MainWindow::on_DateB_clicked()
{
    calendarWindow = new Calendar(this);
    calendarWindow->setModal(false);
    calendarWindow->show();
    connect(calendarWindow, SIGNAL(sendDate(QDate)), this, SLOT(receiveDate(QDate)));
}

void MainWindow::on_History_B_clicked()
{
    calendarWindow = new Calendar(this);
    calendarWindow->setModal(false);
    calendarWindow->show();
    connect(calendarWindow, SIGNAL(sendDate(QDate)), this, SLOT(receiveDate(QDate)));
}

void MainWindow::on_tableWidget_cellDoubleClicked()
{
    on_Add_B_clicked();
}

void MainWindow::fillForm()
{

    if(filling)
    {
        return;
    }
    filling = true;

    //Zamiana daty na taka z 0 na poczatku, jesli dzien lub miesiac jest 1 cyfrowy.
    QString temp = repairDate();

    qry.prepare("SELECT count(u.name) "
                "FROM training_day td "
                "JOIN exercise_training_day et ON et.id_training_day = td.id_training_day "
                "JOIN exercises_set e ON e.id_exercise = et.id_exercise "
                "JOIN user u ON u.id_user = td.id_user "
                "JOIN exercise_groups eg ON eg.id_exercise_group = e.id_exercise_group "
                "WHERE u.id_user = :i AND td.d = :temp "
                "ORDER BY e.name;");
    qry.bindValue(":i", id);
    qry.bindValue(":temp", QString(temp));
    qry.exec();
    qry.first();
    ui->tableWidget->setRowCount(qry.value(0).toInt());

    qry.prepare("SELECT e.name, et.reps, et.weight, eg.name "
                "FROM training_day td "
                "JOIN exercise_training_day et ON et.id_training_day = td.id_training_day "
                "JOIN exercises_set e ON e.id_exercise = et.id_exercise "
                "JOIN user u ON u.id_user = td.id_user "
                "JOIN exercise_groups eg ON eg.id_exercise_group = e.id_exercise_group "
                "WHERE u.id_user = :i AND td.d = :temp "
                "ORDER BY e.name;");
    qry.bindValue(":i", id);
    qry.bindValue(":temp", QString(temp));
    if(qry.exec())
    {
        int row=0;
        for(qry.first(); qry.isValid(); qry.next(), ++row)
        {
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(qry.value(0).toString()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(qry.value(1).toString()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(qry.value(2).toString()));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(qry.value(3).toString()));
        }
    }

    filling = false;

}

QString MainWindow::repairDate()
{
    QString day;
    QString month;

    if(trainingDate.day()<10)
    {
        day = QString("0%1").arg(trainingDate.day());
    }
    else
    {
        day = QString("%1").arg(trainingDate.day());
    }

    if(trainingDate.month()<10)
    {
        month = QString("0%1").arg(trainingDate.month());
    }
    else
    {
        month = QString("%1").arg(trainingDate.month());
    }

    QString year = QString("%1").arg(trainingDate.year());

    QString temp = year+"-"+month+"-"+day;
    return temp;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
       if(event->key() == Qt::Key_Backspace)
       {
           ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
}

void MainWindow::on_Graphs_B_clicked()
{
    chartsWindow = new chartsOption(this, mydb, id);
    chartsWindow->setModal(false);
    chartsWindow->show();
}


void MainWindow::on_exitB_clicked()
{
    free(mydb);
    free(calendarWindow);
    free(windowExercise);
    free(chartsWindow);
    QApplication::quit();
    //close();
}

