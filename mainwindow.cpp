#include <QMessageBox>
#include <QInputDialog>
#include <QThread>
#include <QMutex>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "alerter.h"
#include "setinfo.h"
#include "calendar.h"
#include "timer.h"
#include "studytimer.h"
#include "notepad.h"
#include "checklist.h"
#include "voicecommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // set up calendar alerter thread
    QMutex* mtx_cal = new QMutex;
    calAlerter->setMutex(mtx_cal);
    cal->setMutex(mtx_cal);

    cal->setAQ(calAlerter->alertsQueue);
    cal->setRef(cal);

    connect(&calAlerterThread, &QThread::finished, calAlerter, &QObject::deleteLater);
    connect(this, &MainWindow::cal_start_listening, calAlerter, &Alerter::waitForAlert);
    connect(calAlerter, &Alerter::alert, this, &MainWindow::cal_display_alert, Qt::QueuedConnection);
    connect(this, &MainWindow::cal_alert_displayed, cal, &Calendar::remove_cItem);
    connect(this, &MainWindow::stop_calAlerterThread, calAlerter, &Alerter::exit_thread);

    calAlerter->moveToThread(&calAlerterThread);
    calAlerterThread.start();
    emit cal_start_listening(calAlerter->alertsQueue);

    // set up timer alerter thread
    QMutex* mtx_tTimer = new QMutex;
    tTimerAlerter->setMutex(mtx_tTimer);
    tTimer->setMutex(mtx_tTimer);

    tTimer->setAQ(tTimerAlerter->alertsQueue);
    tTimer->setRef(tTimer);

    connect(&tTimerAlerterThread, &QThread::finished, tTimerAlerter, &QObject::deleteLater);
    connect(this, &MainWindow::tTimer_start_listening, tTimerAlerter, &Alerter::waitForAlert);
    connect(tTimerAlerter, &Alerter::alert, this, &MainWindow::tTimer_display_alert, Qt::QueuedConnection);
    connect(this, &MainWindow::tTimer_alert_displayed, tTimer, &Timer::remove_tItem);
    connect(this, &MainWindow::stop_tTimerAlerterThread, tTimerAlerter, &Alerter::exit_thread);

    tTimerAlerter->moveToThread(&tTimerAlerterThread);
    tTimerAlerterThread.start();
    emit tTimer_start_listening(tTimerAlerter->alertsQueue);

    // set up stimer alerter thread
    QMutex* mtx_sTimer = new QMutex;
    sTimerAlerter->setMutex(mtx_sTimer);
    sTimer->setMutex(mtx_sTimer);

    sTimer->setAQ(sTimerAlerter->alertsQueue);
    sTimer->setRef(sTimer);

    connect(&sTimerAlerterThread, &QThread::finished, sTimerAlerter, &QObject::deleteLater);
    connect(this, &MainWindow::sTimer_start_listening, sTimerAlerter, &Alerter::waitForAlert);
    connect(sTimerAlerter, &Alerter::alert, this, &MainWindow::sTimer_display_alert, Qt::QueuedConnection);
    connect(this, &MainWindow::sTimer_alert_displayed, sTimer, &StudyTimer::remove_sTItem);
    connect(this, &MainWindow::stop_sTimerAlerterThread, sTimerAlerter, &Alerter::exit_thread);

    sTimerAlerter->moveToThread(&sTimerAlerterThread);
    sTimerAlerterThread.start();
    emit sTimer_start_listening(sTimerAlerter->alertsQueue);

    ui->setupUi(this);

    // set up lpListener thread

    connect(&lpListenerThread, &QThread::finished, lpListener, &QObject::deleteLater);
    connect(this, &MainWindow::voice_command_received, lpListener, &VoiceCommand::receive_command);
    connect(lpListener, &VoiceCommand::create_timer, tTimer, &Timer::voice_create_timer);
    connect(lpListener, &VoiceCommand::create_studytimer, sTimer, &StudyTimer::voice_create_studytimer);
    connect(lpListener, &VoiceCommand::create_note, notepad, &Notepad::voice_create_note);
    connect(lpListener, &VoiceCommand::create_checklistItem, checklist, &Checklist::voice_create_item);
    connect(lpListener, &VoiceCommand::create_calendarEvent, cal, &Calendar::voice_create_event);

    lpListener->moveToThread(&lpListenerThread);
    lpListenerThread.start();

}

void MainWindow::on_voiceInput_clicked()
{
    bool ok;
    QString command = QInputDialog::getText(0, "Voice Command",
                "Enter natural language command", QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        voice_command_received(command);
    }
}

MainWindow::~MainWindow()
{
    calAlerterThread.quit();
    calAlerterThread.wait();
    delete calAlerter;
    delete cal;

    tTimerAlerterThread.quit();
    tTimerAlerterThread.wait();
    delete tTimerAlerter;
    delete tTimer;

    sTimerAlerterThread.quit();
    sTimerAlerterThread.wait();
    delete sTimerAlerter;
    delete sTimer;

    delete notepad;
    delete checklist;

    delete lpListener;

    delete ui;
}

void MainWindow::on_shutdown_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "ShutDown",
                "Are you sure you want to shutdown?", QMessageBox::Yes | QMessageBox:: No);

    if(reply == QMessageBox::Yes){
        calAlerterThread.requestInterruption();
        tTimerAlerterThread.requestInterruption();
        sTimerAlerterThread.requestInterruption();
        lpListenerThread.requestInterruption();

        emit stop_calAlerterThread();
        emit stop_tTimerAlerterThread();
        emit stop_sTimerAlerterThread();


        QApplication::quit();
     }
}

void MainWindow::on_guide_clicked()
{
    QMessageBox::aboutQt(this,"Smart Home Assistant");
}

void MainWindow::on_setting_clicked()
{
    SetInfo s;
    s.setModal(true);
    s.exec();
}

void MainWindow::on_notepad_clicked()
{
    notepad->setModal(true);
    notepad->exec();
}

void MainWindow::on_checklist_clicked()
{
    checklist->setModal(true);
    checklist->exec();
}

void MainWindow::on_calendar_clicked()
{
    cal->setModal(true);
    cal->exec();
}

void MainWindow::on_timer_clicked()
{
    tTimer->setModal(true);
    tTimer->exec();
}

void MainWindow::on_studytimer_clicked()
{
    sTimer->setModal(true);
    sTimer->exec();
}

void MainWindow::cal_display_alert(Alert* a){
    bool acquired = false;
    while(!acquired){
        if(calAlerter->getMutex()->try_lock()){
            acquired = true;
            std::string body = a->getAlertBody();
            QString qbody = QString::fromStdString(body);

            QMessageBox::information(0,"ALERT",qbody);
            QApplication::beep(); QApplication::beep();

            calAlerter->getMutex()->unlock();
            emit cal_alert_displayed(a);
        }
    }
}

void MainWindow::tTimer_display_alert(Alert* a)
{
    bool acquired = false;
    while(!acquired){
        if(tTimerAlerter->getMutex()->try_lock()){
            acquired = true;
            std::string body = a->getAlertBody();
            QString qbody = QString::fromStdString(body);

            QMessageBox::information(0,"ALERT",qbody);
            QApplication::beep(); QApplication::beep();

            tTimerAlerter->getMutex()->unlock();
            emit tTimer_alert_displayed(a);
        }
    }
}

void MainWindow::sTimer_display_alert(Alert* a)
{
    bool acquired = false;
    while(!acquired){
        if(sTimerAlerter->getMutex()->try_lock()){
            acquired = true;
            std::string body = a->getAlertBody();
            QString qbody = QString::fromUtf8(body.c_str());

            QMessageBox::information(0,"ALERT",qbody);
            QApplication::beep(); QApplication::beep();

            sTimerAlerter->getMutex()->unlock();
            emit sTimer_alert_displayed(a);
        }
    }
}

