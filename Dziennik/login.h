#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include "mainwindow.h"
#include "registeruser.h"

//extern QString name;
//extern QString surname;

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();



private slots:
    void on_acceptB_clicked();

    void on_DeclineB_clicked();

    void on_registerB_clicked();

private:
    Ui::login *ui;

    MainWindow *dataWindow;
    registerUser *registerWindow;
    QSqlDatabase mydb;


};

#endif // LOGIN_H
