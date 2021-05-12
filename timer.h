#ifndef TIMER_H
#define TIMER_H
#include <QDialog>
#include <QMutex>
#include <QListWidgetItem>

#include "alert.h"
//#include "alerttime.h"

namespace Ui {
class Timer;
}

class Timer : public QDialog
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

	/**
	 * @name Set Timer's Reference
	 * @brief Sets the timer's stored reference.
	 * @param c The Timer to be stored in this calendar's reference.
	 * @return Void.
	 *
	 * Sets the timer's stored reference to the provided Timer object.
	 */
    void setRef(Timer* c);
	/**
	 * @name Set Timer's Alerts Queue
	 * @brief Sets the timer's alerts queue.
	 * @param alertsQueue The alerts queue for the timer.
	 * @return Void.
	 *
	 * Sets the timer's alerts queue to the provided alerts queue.
	 */
    void setAQ(std::vector<Alert*>* alertsQueue);
	/**
	 * @name Set Timer's Designated Mutex
	 * @brief Sets the timer's designated mutex.
	 * @param m The mutex belonging to the timer.
	 * @return Void.
	 *
	 * Sets the timer's designated mutex to the provided QMutex.
	 */
    void setMutex(QMutex* m);

private:
    Ui::Timer *ui;
    Timer* ref;
    QMutex* mtx;
    //AlertTime endtime;
    QDateTime endtime;

    std::vector<Alert*>* aQ;

    QListWidgetItem* currentTItem;
	/**
	 * @name currentTItem setter
	 * @brief Sets currentTItem to the given QListWidgetItem.
	 * @return Void.
	 *
	 * Sets the pointer to the current timer to point to the given QListWidgetItem.
	 */
    void setCurrentListWidgetItem(QListWidgetItem*);

	/**
	 * @name Timer Alert Getter
	 * @brief Returns a pointer to the Alert corresponding to the provided QListWidgetItem.
	 * @return A pointer to the Alert corresponding to the provided QListWidgetItem
	 *
	 * Returns a pointer to the Alert corresponding to the provided QListWidgetItem.
	 */
    Alert* getAlert(QListWidgetItem*);
    std::map<QListWidgetItem*, Alert*> alertWidgetMap;

	/**
	 * @name Time to Alert
	 * @brief Returns a string with the hours, minutes, and seconds left until the timer goes off.
	 * @param inputAlertTime The time at which the timer will go off.
	 * @return A string formatted as "[Hours] hours, [Minutes] minutes, and [Seconds] seconds left."
	 *
	 * Returns a string with the hours, minutes, and seconds left until the timer goes off, formatted as "[Hours] hours, [Minutes] minutes, and [Seconds] seconds left.".
	 */
    std::string timeToAlert(QDateTime inputAlertTime);

private slots:
    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_startTimer_clicked();
    void on_stopTimer_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

public slots:
	/**
	 * @name Delete TItem
	 * @brief Deletes the tItem corresponding to Alert a.
	 * @param a The alert
	 * @return Void.
	 *
	 * Deletes the tItem corresponding to Alert a.
	 */
    void remove_tItem(Alert* a);

	/**
	 * @name Automated Timer Creator
	 * @brief Creates a timer based on the provided int and string.
	 * @return Void.
	 *
	 * Creates a timer based on the provided int and string, without looking for user input. Meant for use with voice commands.
	 */
    void voice_create_timer(int, QString);
};

#endif // TIMER_H
