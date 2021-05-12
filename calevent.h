#ifndef CALEVENT_H
#define CALEVENT_H

#include <string>
#include <QObject>
#include <QDateTime>

#include "lockable.h"
//#include "alerttime.h"

/**
* @brief Class for setting and getting events referenced by the Calendar.
* @author Sam Ahsan
*
* This class is used to hold the time and description of an event created and
* set by the Calendar.
*/
class CalEvent : public QObject, public Lockable
{
    Q_OBJECT

private:
    QDateTime starttime;
    std::string description;

public:
        /**
           * @name Constructor.
           * @brief Alert created with title and time set by the given parameters.
           * @param std::string and AlertTime values initialize the object
           *
           * Alerts are created and stored by the Timer, StudyTimer, and
           * Calendar classes. Alerts are added to a queue held by the Alerter.
           */
    explicit CalEvent(QObject *parent = nullptr);
    ~CalEvent();

    void setStarttime(QDateTime);
    void setDescription(std::string);

    QDateTime getStarttime();
    std::string getDescription();
};

#endif // CALEVENT_H
