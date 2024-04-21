#include "chartsoption.h"
#include "ui_chartsoption.h"


chartsOption::chartsOption(QWidget *parent, QSqlDatabase *db, int x) :
    QDialog(parent),
    mydb(db),
    ui(new Ui::chartsOption),
    id(x)
{
    ui->setupUi(this);

    mydb->open();
    filling=false;
    fillComboBox();
}

chartsOption::~chartsOption()
{
    delete ui;
}

void chartsOption::on_chartB_clicked()
{
    int howMany=0;
    QDate begin = ui->beginD->date();
    QDate end = ui->endD->date();
    QString name = ui->Name_CB->currentText();

    QString dbegin = repairDate(begin);
    QString dend = repairDate(end);

    if(filling)
    {
        return;
    }
    filling = true;

    qry.prepare("SELECT id_exercise FROM exercises_set "
                "WHERE name=:name ;");
    qry.bindValue(":name", name);
    qry.exec();
    qry.next();
    int ex_id = qry.value(0).toInt();


    qry.prepare("SELECT SUM(ext.reps*ext.weight) maxvolume, td.d FROM exercise_training_day ext "
                "JOIN training_day td ON td.id_training_day = ext.id_training_day "
                "WHERE ext.id_exercise = :ide AND td.id_user =:id AND td.d>=:dbegin AND td.d<=:dend "
                "GROUP BY td.d ;");
    qry.bindValue(":ide", ex_id);
    qry.bindValue(":id", id);
    qry.bindValue(":dbegin", dbegin);
    qry.bindValue(":dend", dend);

    QLineSeries *series = new QLineSeries();
    int max=0;

    qry.exec();
    while(qry.next())
    {
        howMany++;
        double maxVolume = qry.value(0).toDouble();
        if(maxVolume>max)
        {
            max=maxVolume;
        }
        QDate tempD = qry.value(1).toDate();
        //qDebug()<<tempD;
        QDateTime momentInTime;
        momentInTime.setDate(tempD);
        //qDebug()<<momentInTime;
        series->append(momentInTime.toMSecsSinceEpoch(), maxVolume);
    }



    filling = false;

    chartWindow = new chart(this, series, howMany, max);
    chartWindow->setModal(true);
    chartWindow->show();




}


void chartsOption::on_ranking_clicked()
{
    rankingWindow = new ranking(this, mydb);
    rankingWindow->setModal(true);
    rankingWindow->show();
}



void chartsOption::on_GroupEx_CB_textActivated(const QString &arg1)
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

}

void chartsOption::fillComboBox()
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

QString chartsOption::repairDate(QDate temp)
{
    QString day;
    QString month;

    if(temp.day()<10)
    {
        day = QString("0%1").arg(temp.day());
    }
    else
    {
        day = QString("%1").arg(temp.day());
    }

    if(temp.month()<10)
    {
        month = QString("0%1").arg(temp.month());
    }
    else
    {
        month = QString("%1").arg(temp.month());
    }

    QString year = QString("%1").arg(temp.year());

    QString tempreturn = year+"-"+month+"-"+day;
    return tempreturn;
}


void chartsOption::on_pushButton_clicked()
{
    close();
}

