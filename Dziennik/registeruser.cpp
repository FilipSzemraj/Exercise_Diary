#include "registeruser.h"
#include "ui_registeruser.h"
#include <QMessageBox>

registerUser::registerUser(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    mydb(db),
    ui(new Ui::registerUser)
{
    ui->setupUi(this);

    mydb->open();
    filling=false;
}

registerUser::~registerUser()
{
    delete ui;
}

void registerUser::on_registerB_clicked()
{
    QString name = ui->ImieLE->text();
    QString surname = ui->NazwiskoLE->text();
    int x=0;

    if(qry.exec("SELECT * FROM user;"))
    {
        while(qry.next())
        {
            QString temp_username = qry.value(1).toString();
            QString temp_password = qry.value(2).toString();
            if(name == temp_username && surname == temp_password)
            {
                x=1;
            }
        }
            if(x==1)
            {
                QMessageBox::about(this, "Uwaga!", "Uzytkownik z podanymi danymi juz istnieje");
            }
            else
            {
                qry.prepare("INSERT INTO user(name, surname) VALUES (:n, :s);");
                qry.bindValue(":n", name);
                qry.bindValue(":s", surname);
                if(qry.exec())
                {
                    QMessageBox::about(this, "Gratulacje!", "Uzytkownik: "+name+" "+surname+" zostal dodany...");
                }
            }

    }
}


void registerUser::on_declineB_clicked()
{
    close();
}

