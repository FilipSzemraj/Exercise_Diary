//#include "mainwindow.h"
#include "login.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    login loginWindow;
    loginWindow.show();

    return a.exec();
}
