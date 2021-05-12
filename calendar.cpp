#include <QInputDialog>
#include <QMessageBox>
#include <QMutex>
#include <string>
#include <vector>
#include <algorithm>

#include "ui_calendar.h"
#include "calendar.h"
#include "calevent.h"
#include "caleventoption.h"
#include "editeventdialog.h"
#include "alert.h"

#include<QDebug>
Calendar::Calendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setDisplayFormat("dd-MM-yyyy hh:mm:ss ap");
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::setRef(Calendar* c)
{
    ref = c;
}

void Calendar::setAQ(std::vector<Alert*>* alertsQueue)
{
    aQ = alertsQueue;
}

void Calendar::setMutex(QMutex* m)
{
    mtx = m;
}

void Calendar::setCurrentCItem(QListWidgetItem* cItem)
{
    currentCItem = cItem;
}

Alert* Calendar::getAlert(CalEvent* cEvent)
{
    auto it = eventAlertMap.find(cEvent);
    if (it != eventAlertMap.end()){
        return it->second;
    }
    return nullptr;
}

CalEvent* Calendar::getEvent(QListWidgetItem* cItem)
{
    auto it = eventWidgetMap.find(cItem);
    if (it != eventWidgetMap.end()){
        return it->second;
    }
    return nullptr;
}

bool Calendar::createEvent()
{
    bool ok;
    QString inputdescr = QInputDialog::getText(0,"New Event Description",
            "Enter event description below", QLineEdit::Normal, QString(), &ok);
    if (!ok || inputdescr == ""){
        return false;
    }
    std::string inputdescr_str = inputdescr.toStdString();

    CalEvent *cEvent = new CalEvent;
    cEvent->setStarttime(newEventTime);
    cEvent->setDescription(inputdescr_str);

    QListWidgetItem* listEvent = new QListWidgetItem;
    listEvent->setText(inputdescr);
    ui->listWidget->addItem(listEvent);

    Alert* newAlert = new Alert(cEvent->getDescription(), cEvent->getStarttime());

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

    eventAlertMap.insert({cEvent, newAlert});
    eventWidgetMap.insert({listEvent, cEvent});

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Lock Event",
                "Do you want to lock this event?", QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::Yes)
    {
        QString inputpswd = QInputDialog::getText(0,"Create password",
                "Enter password for this event:", QLineEdit::Normal, QString(), &ok);
        if (ok)
        {
            std::string inputpswd_str = inputpswd.toStdString();
            cEvent->lock(inputpswd_str);
        }
    }
    return true;
}

bool Calendar::deleteEvent(CalEvent* cEvent, QListWidgetItem* cItem)
{
    if(cEvent->isLocked())
    {
        bool ok;

        QString inputpswd = QInputDialog::getText(0,"Event Locked","Enter password:",
                                    QLineEdit::Normal, QString(), &ok);
        if (!ok)
        {
            ui->pushButton->setEnabled(false);
            return false;
        }
        std::string inputpswd_str = inputpswd.toStdString();

        if (!(cEvent->unlock(inputpswd_str))) {
            QMessageBox::information(0,"","Incorrect Password. Event not deleted.");
            ui->pushButton->setEnabled(false);
            return false;
        }
    }

    Alert* oldAlert = getAlert(cEvent);
    bool acquired = false;

    while(!acquired)
    {
        if(mtx->try_lock())
        {
            acquired = true;
            aQ->erase(std::find(aQ->begin(), aQ->end(), oldAlert));
            mtx->unlock();
        }
    }

    eventAlertMap.erase(cEvent);
    eventWidgetMap.erase(cItem);
    cItem->setHidden(true);

    delete oldAlert;
    delete cEvent;
    delete cItem;


    QMessageBox::information(0,"","Event deleted.");
    return true;
}

bool Calendar::editEvent(CalEvent* cEvent, QListWidgetItem* cItem)
{
    bool ok;

    bool relock_after_edit = false;
    std::string pswd;

    if(cEvent->isLocked())
    {
        relock_after_edit = true;

        QString inputpswd = QInputDialog::getText(0,"Event Locked","Enter password:",
                                                QLineEdit::Normal, QString(), &ok);

        std::string inputpswd_str = inputpswd.toStdString();
        if (!ok)
        {
                ui->pushButton->setEnabled(false);
                return false;
        }

        if (!(cEvent->unlock(inputpswd_str))) {
            QMessageBox::information(0,"","Incorrect Password. Event not updated.");
            ui->pushButton->setEnabled(false);
            return false;
        }
    }

    QString inputdescr = QInputDialog::getText(0,"Edit Event Description",
            "Enter event description below", QLineEdit::Normal, QString(), &ok);

    if (!ok || inputdescr == "")
    {
        ui->pushButton->setEnabled(false);
        return false;
    }

    std::string inputdescr_str = inputdescr.toStdString();

    EditEventDialog editDateTime(this);
    editDateTime.exec();

    cEvent->setStarttime(newEventTime);
    cEvent->setDescription(inputdescr_str);

    cItem->setText(inputdescr);

    Alert* newAlert = new Alert(cEvent->getDescription(), cEvent->getStarttime());
    Alert* oldAlert = getAlert(cEvent);

    bool acquired = false;
    while(!acquired){
        if(mtx->try_lock()){
            acquired = true;

            aQ->erase(std::find(aQ->begin(), aQ->end(), oldAlert));
            delete oldAlert;

            aQ->push_back(newAlert);
            mtx->unlock();
         }
    }
    eventAlertMap.erase(cEvent);
    eventAlertMap.insert({cEvent, newAlert});

    QMessageBox::information(0,"","Event updated.");

    if(relock_after_edit)
    {
        cEvent->lock();
    }
    return true;
}

void Calendar::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->pushButton->setEnabled(true);
    newEventTime = dateTime;

}

void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    newEventTime.setDate(date);

    ui->dateTimeEdit->setDate(date);
    ui->pushButton->setEnabled(true);
}

void Calendar::on_pushButton_clicked()
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime event;

    if (now.secsTo(newEventTime) < 0)
    {
        QMessageBox::information(0,"Error","Cannot create an event in the past.");
        ui->pushButton->setEnabled(false);
        return;
    }

    ref->createEvent();
}

void Calendar::on_listWidget_itemActivated(QListWidgetItem *item)
{
    QDateTime t = getAlert(getEvent(item))->getAlertTime();

    QMessageBox::information(0,"Event date:", t.toString());

    CalEventOption option(this, item);
    option.exec();
}

void Calendar::delete_selected(QListWidgetItem* cItem)
{
    if (getEvent(cItem) == nullptr)
    {
        QMessageBox::information(0,"Error","Event not found.");
        ui->pushButton->setEnabled(false);
        return;
    }

    ref->deleteEvent(getEvent(cItem), cItem);
}

void Calendar::edit_selected(QListWidgetItem* cItem)
{
    ui->pushButton->setEnabled(false);

    if (getEvent(cItem) == nullptr)
    {
        QMessageBox::information(0,"Error","Event not found.");
        ui->pushButton->setEnabled(false);
        return;
    }

    ref->editEvent(getEvent(cItem), cItem);
}

void Calendar::remove_cItem(Alert* a)
{
    CalEvent* remove_cEvent = nullptr;
    QListWidgetItem* remove_CItem = nullptr;
    bool found = false;
    for (auto it_1 = eventAlertMap.begin(); it_1 != eventAlertMap.end(); ++it_1){
        if (it_1->second == a)
        {
            remove_cEvent = it_1->first;

            for (auto it_2 = eventWidgetMap.begin(); it_2 != eventWidgetMap.end(); ++it_2)
            {
                remove_CItem = it_2->first;
                found = true;
                eventWidgetMap.erase(it_2->first);
                break;
            }
        }
        if (found) { break; }
    }

    delete a;

    if (remove_cEvent != nullptr)
    {
        delete remove_cEvent;
    }

    if (remove_CItem != nullptr)
    {
        delete remove_CItem;
    }
}

void Calendar::timeEdited(QDateTime* t)
{
    newEventTime = *t;
}

void Calendar::voice_create_event(int time, QString title)
{
    // create AlertTime from int* then create new event
}
