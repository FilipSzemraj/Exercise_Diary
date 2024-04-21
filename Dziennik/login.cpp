#include "login.h"
#include "ui_login.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{

    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("baza_dziennik.db");
    if(mydb.open())
    {
        qDebug()<<"Database opened!";
    }
    else
    {
        qDebug() << "Error = "<< mydb.lastError();
    }
}

login::~login()
{
    delete ui;
}

void login::on_acceptB_clicked()
{

    QString username = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();


    QSqlQuery qry;

    if(qry.exec("SELECT * FROM user;"))
    {
        while(qry.next())
        {
            QString temp_username = qry.value(1).toString();
            QString temp_password = qry.value(2).toString();
            if(username == temp_username && password == temp_password)
            {
                QMessageBox::about(this, "Logowanie!", "Zalogowano pomyślnie");
                dataWindow = new MainWindow(nullptr, mydb, username, password);
                dataWindow->show();
                //login::deleteLater();
                //close();
                login::~login();
                return;
            }
        }
        QMessageBox::about(this, "Bląd!", "Nie ma użytkownika z takimi danymi, przejdź do rejestracji...");
    }

}



void login::on_DeclineB_clicked()
{
    close();
}





void login::on_registerB_clicked()
{
    registerWindow = new registerUser(this, &mydb);
    registerWindow->setModal(true);
    registerWindow->show();
}

