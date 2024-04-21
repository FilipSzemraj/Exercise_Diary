#include "calendar.h"
#include "ui_calendar.h"

Calendar::Calendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);

}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::on_calendarWidget_selectionChanged()
{

    QDate d(ui->calendarWidget->selectedDate());
    emit sendDate(d);
}

