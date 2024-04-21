#ifndef ADDING_NEW_EXERCISE_H
#define ADDING_NEW_EXERCISE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>
#include <QMessageBox>
#include "adding_new_group.h"

namespace Ui {
class adding_new_exercise;
}

class adding_new_exercise : public QDialog
{
    Q_OBJECT

    QSqlDatabase *mydb;

public:
    explicit adding_new_exercise(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~adding_new_exercise();

private slots:
    void on_Add_new_gr_B_clicked();

    void on_Add_new_ex_B_clicked();

    void on_DeclineB_clicked();

private:
    Ui::adding_new_exercise *ui;
    void fillComboBox();
    adding_new_group *newGroupWindow;
    QSqlQuery qry;
    bool filling;
};

#endif // ADDING_NEW_EXERCISE_H
