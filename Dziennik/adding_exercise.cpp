#include "adding_exercise.h"
#include "ui_adding_exercise.h"
#include <QtCore>
#include <QtGui>

adding_exercise::adding_exercise(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    mydb(db),
    ui(new Ui::adding_exercise)
{
    ui->setupUi(this);


    mydb->open();
    filling=false;
    fillComboBox();
}

adding_exercise::~adding_exercise()
{
    delete ui;
}

void adding_exercise::fillComboBox()
{
    if(filling)
    {
        return;
    }
    filling = true;
    QString temp;

    if(qry.exec("SELECT name FROM exercise_groups;"))
    {
        qry.next();
        temp = qry.value(0).toString();
        do{
            ui->GroupEx_CB->addItem(qry.value(0).toString());
        }while(qry.next());
    }

    filling = false;
    on_GroupEx_CB_textActivated(temp);
}




void adding_exercise::on_GroupEx_CB_textActivated(const QString &arg1)
{
    if(filling)
    {
        return;
    }
    filling = true;

    QString temp;

    ui->Name_CB->clear();

    qry.prepare("SELECT es.name FROM exercise_groups eg "
                "JOIN exercises_set es ON es.id_exercise_group = eg.id_exercise_group "
                "WHERE eg.name = :group ;");
    qry.bindValue(":group", arg1);

    if(qry.exec())
    {
        qry.next();
        temp = qry.value(0).toString();
        do{
            ui->Name_CB->addItem(qry.value(0).toString());
        }while(qry.next());
    }

    filling = false;
    on_Name_CB_textActivated(temp);
}


void adding_exercise::on_Name_CB_textActivated(const QString &arg1)
{
    if(filling)
    {
        return;
    }
    filling = true;

    ui->Description_TB->clear();

    qry.prepare("SELECT es.description FROM exercise_groups eg "
                "JOIN exercises_set es ON es.id_exercise_group = eg.id_exercise_group "
                "WHERE es.name = :name ;");
    qry.bindValue(":name", arg1);

    qry.exec();

    qry.next();
    ui->Description_TB->setText(qry.value(0).toString());



    filling = false;
}


void adding_exercise::on_DeclineB_clicked()
{
    close();
}


void adding_exercise::on_AcceptB_clicked()
{
    int reps = ui->RepsS->value();
    double weight = ui->WeightDS->value();
    QString group = ui->GroupEx_CB->currentText();
    QString name = ui->Name_CB->currentText();
    if(reps!=0 && !(group.isEmpty()) && !(name.isEmpty()))
    {
        emit sendDateForm(reps, weight ,group, name);
    }

}



void adding_exercise::on_addNewExB_clicked()
{
    newExerciseWindow = new adding_new_exercise(this, mydb);
    newExerciseWindow->setModal(true);
    newExerciseWindow->show();
}

