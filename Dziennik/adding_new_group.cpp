#include "adding_new_group.h"
#include "ui_adding_new_group.h"

adding_new_group::adding_new_group(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    mydb(db),
    ui(new Ui::adding_new_group)
{
    ui->setupUi(this);

    mydb->open();
    filling=false;
}

adding_new_group::~adding_new_group()
{
    delete ui;
}

void adding_new_group::on_DeclineB_clicked()
{
    close();
}


void adding_new_group::on_AcceptB_clicked()
{
    QString name = ui->nameNewGroupL->text();
    if(name!=nullptr)
    {
        if(filling)
        {
            return;
        }
        filling = true;

        qry.prepare("SELECT name FROM exercise_groups;");
        if(qry.exec())
        {
            while(qry.next())
            {
                if(qry.value(0) == name)
                {
                    QMessageBox::about(this, "Uwaga!", "Grupa o takiej nazwie już istnieje...");
                    return;
                }
            }
        }

        qry.prepare("INSERT INTO exercise_groups(name) "
                    "VALUES(:n);");
        qry.bindValue(":n", name);
        if(qry.exec())
        {
            QMessageBox::about(this, "Gratulacje!", "Dodano pomyślnie grupe o nazwie: "+name);
        }

        filling = false;

    }

}

