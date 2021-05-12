#ifndef STUDYTIMER_H
#define STUDYTIMER_H
#include <QDialog>
#include <QMutex>
#include <QListWidgetItem>

#include "alert.h"
//#include "alerttime.h"

namespace Ui {
class StudyTimer;
}

class StudyTimer : public QDialog
{
    Q_OBJECT

public:
    explicit StudyTimer(QWidget *parent = nullptr);
    ~StudyTimer();

	/**
	 * @name Set StudyTimer's Reference
	 * @brief Sets the study timer's stored reference.
	 * @param c The StudyTimer to be stored in this calendar's reference.
	 * @return Void.
	 *
	 * Sets the study timer's stored reference to the provided StudyTimer object.
	 */
	void setRef(StudyTimer* c);
	/**
	 * @name Set StudyTimer's Alerts Queue
	 * @brief Sets the study timer's alerts queue.
	 * @param alertsQueue The alerts queue for the study timer.
	 * @return Void.
	 *
	 * Sets the study timer's alerts queue to the provided alerts queue.
	 */
	void setAQ(std::vector<Alert*>* alertsQueue);
	/**
	 * @name Set StudyTimer's Designated Mutex
	 * @brief Sets the study timer's designated mutex.
	 * @param m The mutex belonging to the study timer.
	 * @return Void.
	 *
	 * Sets the study timer's designated mutex to the provided QMutex.
	 */
	void setMutex(QMutex* m);

private:
    Ui::StudyTimer *ui;
    StudyTimer* ref;
    QMutex* mtx;
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
	 * @name StudyTimer Alert Getter
	 * @brief Returns a pointer to the Alert corresponding to the provided QListWidgetItem.
	 * @return A pointer to the Alert corresponding to the provided QListWidgetItem
	 *
	 * Returns a pointer to the Alert corresponding to the provided QListWidgetItem.
	 */
    Alert* getAlert(QListWidgetItem*);
    std::map<QListWidgetItem*, Alert*> alertWidgetMap;
	/**
	 * @name Time to Alert
	 * @brief Returns a string with the hours, minutes, and seconds left until the study timer goes off.
	 * @param inputAlertTime The time at which the study timer will go off.
	 * @return A string formatted as "[Hours] hours, [Minutes] minutes, and [Seconds] seconds left."
	 *
	 * Returns a string with the hours, minutes, and seconds left until the timer goes off, formatted as "[Hours] hours, [Minutes] minutes, and [Seconds] seconds left.".
	 */
    std::string timeToAlert(QDateTime inputAlertTime);

private slots:
    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_startStudyTimer_clicked();
    void on_stopStudyTimer_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

public slots:
	/**
	 * @name Delete STItem
	 * @brief Deletes the stItem corresponding to Alert a.
	 * @param a The alert
	 * @return Void.
	 *
	 * Deletes the stItem corresponding to Alert a.
	 */
    void remove_sTItem(Alert* a);

	/**
	 * @name Automated Study Timer Creator
	 * @brief Creates a study timer based on the provided int and string.
	 * @return Void.
	 *
	 * Creates a study timer based on the provided int and string, without looking for user input. Meant for use with voice commands.
	 */
    void voice_create_studytimer(int, QString);
};

#endif // STUDYTIMER_H


/*
#ifndef STUDYTIMER_H
#define STUDYTIMER_H

#include <QDialog>
#include <QMutex>
#include <QListWidgetItem>

#include "alert.h"
#include "alerttime.h"

namespace Ui {
	class StudyStudyTimer;
}

class StudyStudyTimer : public QDialog
{
	    Q_OBJECT

public:
    explicit StudyStudyTimer(QWidget *parent = nullptr);
    ~StudyStudyTimer();

    void setRef(StudyStudyTimer*);
    void setAQ(std::vector<Alert*>*);
    void setMutex(QMutex*);

private:
    Ui::StudyStudyTimer *ui;
    StudyStudyTimer* ref;
    QMutex* mtx;
    AlertTime endtime;

    std::vector<Alert*>* aQ;

    QListWidgetItem* currentSTItem;
    void setCurrentListWidgetItem(QListWidgetItem*);

    Alert* getAlert(QListWidgetItem*);
    std::map<QListWidgetItem*, Alert*> alertWidgetMap;

private slots:
    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_startStudyStudyTimer_clicked();
    void on_stopStudyStudyTimer_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

public slots:
    void remove_stItem(Alert*);

    void voice_create_studytimer(int);
};

#endif // STUDYTIMER_H
*/
