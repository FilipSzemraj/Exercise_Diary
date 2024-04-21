#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>

namespace Ui {
class registerUser;
}

class registerUser : public QDialog
{
    Q_OBJECT

    QSqlDatabase *mydb;

public:
    explicit registerUser(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~registerUser();

private slots:
    void on_registerB_clicked();

    void on_declineB_clicked();

private:
    Ui::registerUser *ui;

    QSqlQuery qry;
    bool filling;
};

#endif // REGISTERUSER_H
