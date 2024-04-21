#ifndef ADDING_EXERCISE_H
#define ADDING_EXERCISE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <QDate>
#include "adding_new_exercise.h"

namespace Ui {
class adding_exercise;
}

class adding_exercise : public QDialog
{
    Q_OBJECT

    QSqlDatabase *mydb;

public:
    explicit adding_exercise(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~adding_exercise();

private slots:

    void on_GroupEx_CB_textActivated(const QString &arg1);
    void on_Name_CB_textActivated(const QString &arg1);

    void on_DeclineB_clicked();

    void on_AcceptB_clicked();

    void on_addNewExB_clicked();

private:
    Ui::adding_exercise *ui;

    adding_new_exercise *newExerciseWindow;
    void fillComboBox();
    QSqlQuery qry;
    bool filling;

signals:
    void sendDateForm(int, double ,QString, QString);
};

#endif // ADDING_EXERCISE_H
