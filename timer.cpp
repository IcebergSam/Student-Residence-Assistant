#include <QInputDialog>
#include <QMessageBox>

#include "timer.h"
#include "ui_timer.h"
#include "LanguageParser.h"

#include <QDebug>
Timer::Timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    ui->startTimer->setEnabled(false);
    ui->stopTimer->setEnabled(false);
    ui->timeEdit->setDisplayFormat("hh:mm:ss ap");

}

Timer::~Timer()
{
    delete ui;
}

void Timer::setRef(Timer* c)
{
    ref = c;
}

void Timer::setAQ(std::vector<Alert*>* alertsQueue)
{
    aQ = alertsQueue;
}

void Timer::setMutex(QMutex* m)
{
    mtx = m;
}

void Timer::setCurrentListWidgetItem(QListWidgetItem* tItem)
{
    currentTItem = tItem;
}

Alert* Timer::getAlert(QListWidgetItem* tItem)
{
    auto it = alertWidgetMap.find(tItem);
    if (it != alertWidgetMap.end())
    {
        return it->second;
    }
    return nullptr;
}

std::string Timer::timeToAlert(QDateTime inputAlertTime)
{
    std::string str_time = "";
    int days_left;
    int hours_left;
    int minutes_left;
    int seconds_left;

    QDateTime now = QDateTime::currentDateTime();
    QDateTime alertDateTime = QDateTime::currentDateTime();

    QDate alertDate = alertDateTime.date();
    alertDate.setDate(inputAlertTime.date().year(), inputAlertTime.date().month(), inputAlertTime.date().day());
    alertDateTime.setDate(alertDate);

    QTime alertTime = alertDateTime.time();
    alertTime.setHMS(inputAlertTime.time().hour(), inputAlertTime.time().minute(), inputAlertTime.time().second());
    alertDateTime.setTime(alertTime);

    int secondsToInputTime = now.secsTo(alertDateTime);   //Gets the amount of seconds to the alert

    if(secondsToInputTime < 0) {
        str_time = "Event already done";
        return str_time;
    }

    minutes_left = (secondsToInputTime / 60);  //Gets the amount of full minutes able to be made
    hours_left = (minutes_left / 60);  //Gets the amount of full hours able to be made
    days_left = (hours_left / 24); //Gets the amount of full days able to be made
    hours_left = hours_left % 24;   //Gets the left over hours not able to be made into days
    minutes_left = minutes_left % 60;   //Gets the left over minutes not able to be made into hours
    seconds_left = secondsToInputTime % 60; //Gets leftover seconds

    if(days_left > 0) {
        str_time += std::to_string(days_left);
        str_time += " days, ";
    }

    str_time += std::to_string(hours_left);
    str_time += " hours, ";
    str_time += std::to_string(minutes_left);
    str_time += " minutes, ";
    str_time += std::to_string(seconds_left);
    str_time += " seconds left.";

    return str_time;
}
void Timer::on_timeEdit_userTimeChanged(const QTime &time)
{
    ui->stopTimer->setEnabled(false);
    ui->startTimer->setEnabled(true);

    QDateTime now = QDateTime::currentDateTime();
    QDateTime endDateTime = QDateTime::currentDateTime();
    endDateTime.setTime(time);

    int secondsToInputTime = now.time().secsTo(endDateTime.time());
    if (secondsToInputTime <= 0) // timer is being set for the following day
    {
        endDateTime = endDateTime.addDays(1);
    }

    endtime.setDate(endDateTime.date());
    endtime.setTime(time);
}

void Timer::on_startTimer_clicked()
{
    bool ok;
    QString inputdescr = QInputDialog::getText(0,"New Timer",
            "Enter Timer Name", QLineEdit::Normal, QString(), &ok);
    if (!ok || inputdescr == "")
    {
        ui->startTimer->setEnabled(false);
        ui->stopTimer->setEnabled(false);
        return;
    }

    QListWidgetItem* listAlert = new QListWidgetItem;
    listAlert->setText(inputdescr);
    ui->listWidget->addItem(listAlert);

    std::string inputdescr_str = inputdescr.toStdString();
    Alert* newAlert = new Alert(inputdescr_str, endtime);

    bool acquired = false;
    while(!acquired)
    {
        if(mtx->try_lock())
        {
            acquired = true;
            aQ->push_back(newAlert);
            mtx->unlock();
        }
    }

    alertWidgetMap.insert({listAlert, newAlert});
    ui->startTimer->setEnabled(false);
}

void Timer::on_listWidget_itemClicked(QListWidgetItem *item)
{
    setCurrentListWidgetItem(item);
    ui->startTimer->setEnabled(false);
    ui->stopTimer->setEnabled(true);
}

void Timer::on_stopTimer_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                "Stop Timer", "Are you sure you want to cancel this timer?",
                QMessageBox::Yes | QMessageBox:: No);

    if(reply == QMessageBox::No)
    {
        ui->stopTimer->setEnabled(false);
        return;
    }

    Alert* oldAlert = getAlert(currentTItem);

    bool acquired = false;
    while(!acquired)
    {
        if(mtx->try_lock())
        {
            acquired = true;
            aQ->erase(std::find(aQ->begin(), aQ->end(), oldAlert));
            delete oldAlert;
            mtx->unlock();
        }
    }

    alertWidgetMap.erase(currentTItem);
    currentTItem->setHidden(true);
    ui->stopTimer->setEnabled(false);

    delete currentTItem;
}

void Timer::remove_tItem(Alert* a)
{
    QListWidgetItem* finished_tItem = nullptr;

    bool found = false;
    for (auto it = alertWidgetMap.begin(); it != alertWidgetMap.end(); ++it)
    {
        if (it->second == a)
        {
            found = true;
            finished_tItem = it->first;
            alertWidgetMap.erase(it->first);
            break;
        }
        if (found) { break; }
    }

    if (finished_tItem != nullptr)
    {
        delete finished_tItem;
    }

    delete a;
}

void Timer::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->stopTimer->setEnabled(false);
    ui->startTimer->setEnabled(false);

    Alert *a = getAlert(item);
    //AlertTime t = a->getAlertTime();
    QDateTime t = a->getAlertTime();

    QString str_time = QString::fromStdString(timeToAlert(t));
    QMessageBox::information(0,"Timer:", str_time);
}

void Timer::voice_create_timer(int inputSeconds, QString name)
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime endDateTime = QDateTime::currentDateTime();
    endDateTime = now.addSecs(inputSeconds);

    endtime = endDateTime;
    name = "Timer";

    //std::string inputdescr_str = "Timer";

    //if(name == "") {
    //       std::string inputdescr_str = "New Timer";
    //   } else {
    //       std::string inputdescr_str = name.toStdString();
    //   }

    //QString inputdescr = QString::fromStdString(inputdescr_str);

    QListWidgetItem* listAlert = new QListWidgetItem;

    listAlert->setText(name);
    ui->listWidget->addItem(listAlert);

    Alert* newAlert = new Alert(name.toStdString(), endtime);

    bool acquired = false;
    while(!acquired)
    {
        if(mtx->try_lock())
        {
            acquired = true;
            aQ->push_back(newAlert);
            mtx->unlock();
        }
    }

    alertWidgetMap.insert({listAlert, newAlert});
    ui->stopTimer->setEnabled(false);
    ui->startTimer->setEnabled(false);
}
