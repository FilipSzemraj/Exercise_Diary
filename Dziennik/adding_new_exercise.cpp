#include "adding_new_exercise.h"
#include "ui_adding_new_exercise.h"


adding_new_exercise::adding_new_exercise(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    mydb(db),
    ui(new Ui::adding_new_exercise)
{
    ui->setupUi(this);

    mydb->open();
    filling=false;
    fillComboBox();
}

adding_new_exercise::~adding_new_exercise()
{
    delete ui;
}

void adding_new_exercise::on_Add_new_gr_B_clicked()
{
    newGroupWindow = new adding_new_group(this, mydb);
    newGroupWindow->setModal(true);
    newGroupWindow->show();
}


void adding_new_exercise::on_Add_new_ex_B_clicked()
{
    QString name = ui->NameE->text();
    QString desc = ui->DescPT->toPlainText();
    if(name!=nullptr && desc!=nullptr)
    {
        QString group = ui->GroupExCB->currentText();
        int id_exercise_group;
        qry.prepare("SELECT id_exercise_group FROM exercise_groups "
                    "WHERE name=:g;");
        qry.bindValue(":g", group);
        qry.exec();
        qry.next();
        id_exercise_group=qry.value(0).toInt();

        qry.prepare("SELECT name FROM exercises_set "
                    "WHERE id_exercise_group=:i;");
        qry.bindValue(":i", id_exercise_group);
        if(qry.exec())
        {
            while(qry.next())
            {
                if(qry.value(0) == name)
                {
                    QMessageBox::about(this, "Uwaga!", "Ćwiczenie o takiej nazwie już istnieje...");
                    return;
                }
            }
        }

        qry.prepare("INSERT INTO exercises_set(name, description, id_exercise_group) "
                    "VALUES (:n, :d, :i);");
        qry.bindValue(":n", name);
        qry.bindValue(":d", desc);
        qry.bindValue(":i", id_exercise_group);
        if(qry.exec())
        {
            QMessageBox::about(this, "Gratulacje!", "Pomyslnie dodano ćwiczenie: "+name+" do grupy: "+group);
        }

    }
}


void adding_new_exercise::on_DeclineB_clicked()
{
    close();
}

void adding_new_exercise::fillComboBox()
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
            ui->GroupExCB->addItem(qry.value(0).toString());
        }while(qry.next());
    }

    filling = false;
}

