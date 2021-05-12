#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>
#include <QMutex>
#include <QListWidgetItem>
#include <QDateTime>
#include <QString>
#include <vector>

#include "calevent.h"
#include "alert.h"
//#include "alerttime.h"

namespace Ui {
class Calendar;
}

class Calendar : public QDialog
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    ~Calendar();

	/**
	 * @name Set Calendar's Reference
	 * @brief Sets the calendar's stored reference.
	 * @param c The Calendar to be stored in this calendar's reference.
	 * @return Void.
	 *
	 * Sets the calendar's stored reference to the provided Calendar object.
	 */
    void setRef(Calendar* c);
	/**
	 * @name Set Calendar's Alerts Queue
	 * @brief Sets the calendar's alerts queue.
	 * @param alertsQueue The alerts queue for the calendar.
	 * @return Void.
	 *
	 * Sets the calendar's alerts queue to the provided alerts queue.
	 */
    void setAQ(std::vector<Alert*>* alertsQueue);
	/**
	 * @name Set Calendar's Designated Mutex
	 * @brief Sets the calendar's designated mutex.
	 * @param m The mutex belonging to the calendar.
	 * @return Void.
	 *
	 * Sets the calendar's designated mutex to the provided QMutex.
	 */
    void setMutex(QMutex* m);

    bool createEvent();
    bool deleteEvent(CalEvent*, QListWidgetItem*);
    bool editEvent(CalEvent*, QListWidgetItem*);

private:
    Ui::Calendar *ui;
    Calendar* ref;
    QMutex* mtx;
    QDateTime newEventTime;

    std::vector<Alert*>* aQ;
    std::map<CalEvent*, Alert*> eventAlertMap;
    std::map<QListWidgetItem*, CalEvent*> eventWidgetMap;

    QListWidgetItem* currentCItem;
    void setCurrentCItem(QListWidgetItem*);

    Alert* getAlert(CalEvent*);
    CalEvent* getEvent(QListWidgetItem*);

private slots:
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_calendarWidget_clicked(const QDate &date);
    void on_pushButton_clicked();
    void on_listWidget_itemActivated(QListWidgetItem* item);

public slots:
	/**
	 * @name Delete Selected Event
	 * @brief Deletes the selected event.
	 * @param The QListWidgetItem corresponding to the event to be deleted.
	 * @return Void.
	 *
	 * Deletes the event corresponding to the QListWidgetItem given.
	 */
    void delete_selected(QListWidgetItem*);
	/**
	 * @name Edit Selected Event
	 * @brief Edits the selected event.
	 * @param cItem The QListWidgetItem corresponding to the event to be edited.
	 * @return Void.
	 *
	 * Checks for the existence of the event corresponding to the QListWidgetItem given, and if it exists, opens .
	 */
    void edit_selected(QListWidgetItem* cItem);
	/**
	 * @name Delete CItem
	 * @brief Deletes the cItem corresponding to Alert a.
	 * @param a The alert
	 * @return Void.
	 *
	 * Deletes the cItem corresponding to Alert a.
	 */
    void remove_cItem(Alert* a);
	/**
	 * @name Change newEventTime
	 * @brief Changes newEventTime.
	 * @param t QDateTime object with the new time.
	 * @return Void.
	 *
	 * Changes newEventTime to the time in t.
	 */
    void timeEdited(QDateTime* t);

	/**
	 * @name Automated Calendar Event Creator
	 * @brief Creates a calendar event based on the provided QString and int.
	 * @return Void.
	 *
	 * Creates a calendar event based on the provided QString and int, without looking for user input. Meant for use with voice commands.
	 */
    void voice_create_event(int, QString);
};

#endif // CALENDAR_H
