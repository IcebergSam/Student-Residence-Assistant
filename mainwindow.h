#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "alert.h"
#include "alerter.h"
#include "calendar.h"
#include "timer.h"
#include "studytimer.h"
#include "notepad.h"
#include "checklist.h"
#include "voicecommand.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Calendar* cal = new Calendar;
    Alerter* calAlerter = new Alerter;
    QThread calAlerterThread;

    Timer* tTimer = new Timer;
    Alerter* tTimerAlerter = new Alerter;
    QThread tTimerAlerterThread;

    StudyTimer* sTimer = new StudyTimer;
    Alerter* sTimerAlerter = new Alerter;
    QThread sTimerAlerterThread;

    Notepad* notepad = new Notepad;

    Checklist* checklist = new Checklist;

    VoiceCommand* lpListener = new VoiceCommand;
    QThread lpListenerThread;

private slots:
    void on_shutdown_clicked();
    void on_guide_clicked();
    void on_setting_clicked();
    void on_notepad_clicked();
    void on_calendar_clicked();
    void on_timer_clicked();
    void on_studytimer_clicked();

    void cal_display_alert(Alert*);
    void tTimer_display_alert(Alert*);
    void sTimer_display_alert(Alert*);
    void on_checklist_clicked();
    void on_voiceInput_clicked();

signals:
    void cal_start_listening(std::vector<Alert*>*);
    void tTimer_start_listening(std::vector<Alert*>*);
    void sTimer_start_listening(std::vector<Alert*>*);

    void cal_alert_displayed(Alert*);
    void tTimer_alert_displayed(Alert*);
    void sTimer_alert_displayed(Alert*);

    void stop_calAlerterThread();
    void stop_tTimerAlerterThread();
    void stop_sTimerAlerterThread();

    void voice_command_received(QString);
};

#endif // MAINWINDOW_H
