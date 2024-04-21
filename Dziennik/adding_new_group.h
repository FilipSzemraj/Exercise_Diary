#ifndef ADDING_NEW_GROUP_H
#define ADDING_NEW_GROUP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>
#include <QMessageBox>

namespace Ui {
class adding_new_group;
}

class adding_new_group : public QDialog
{
    Q_OBJECT

    QSqlDatabase *mydb;

public:
    explicit adding_new_group(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~adding_new_group();

private slots:
    void on_DeclineB_clicked();

    void on_AcceptB_clicked();

private:
    Ui::adding_new_group *ui;

    QSqlQuery qry;
    bool filling;
};

#endif // ADDING_NEW_GROUP_H
