#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>
#include <QKeyEvent>
#include "calendar.h"
#include "adding_exercise.h"
#include "chartsoption.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"), QString name="", QString surname="");
    ~MainWindow();

private slots:
    void on_Add_B_clicked();

    void receiveDate(QDate);

    void receiveDateForm(int, double ,QString, QString);

    void on_DateB_clicked();

    void on_History_B_clicked();

    void on_tableWidget_cellDoubleClicked();

    void on_CommitB_clicked();

    void on_Graphs_B_clicked();

    void on_exitB_clicked();

private:
    //4 pierwsze byly wyzej pod Q_OBJECT
    QSqlDatabase *mydb;
    QSqlDatabase mydbP;
    QString name;
    QString surname;
    //

    Ui::MainWindow *ui;
    void fillForm();
    QString repairDate();
    bool filling;
    int id;
    QSqlQuery qry;
    Calendar *calendarWindow;
    adding_exercise *windowExercise;
    chartsOption *chartsWindow;
    QDate trainingDate;

protected:
    void keyPressEvent(QKeyEvent *event) override;



};
#endif // MAINWINDOW_H
