#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>
#include <QDate>
#include <QObject>

namespace Ui {
class Calendar;
}

class Calendar : public QDialog
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    ~Calendar();


private slots:
    void on_calendarWidget_selectionChanged();

private:
    Ui::Calendar *ui;

signals:
    void sendDate(QDate);




};

#endif // CALENDAR_H
