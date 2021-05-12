#ifndef ALERT_H
#define ALERT_H
#include <string>
#include <QDateTime>

/**
* @brief Class for setting and getting alerts.
* @author Sam Ahsan
*
* This class is used to hold the title and time of
* an alert set by the timer, studytimer, and the calendar.
*/
class Alert
{
	private:
        std::string alertBody;
        QDateTime alertTime;

        /**
           * @name Alert body setter.
           * @brief Sets the private Alert attribute 'alertBody'.
           * @return Void.
           *
           * This function is used by the Timer, StudyTimer, and Calendar
           * classes to set the body of a particular Alert as per user input.
           */
        void setAlertBody(std::string);
        /**
           * @name Alert time setter.
           * @brief Sets the private Alert attribute 'alertTime'.
           * @return Void.
           *
           * This function is used by the Timer, StudyTimer, and Calendar
           * classes to set the time of a particular Alert as per user input.
           */
        void setAlertTime(QDateTime);

	public:
        /**
           * @name Constructor.
           * @brief Alert created with title and time set by the given parameters.
           * @param std::string and QDateTime values initialize the object
           *
           * Alerts are created and stored by the Timer, StudyTimer, and
           * Calendar classes. Alerts are added to a queue held by the Alerter.
           */
        Alert(std::string, QDateTime);
        /**
           * @name Destructor.
           * @brief Alerts are destroyed as per C++ destruction.
           */
        ~Alert();

        /**
           * @name Alert body getter.
           * @brief Gets the private Alert attribute 'alertBody'.
           * @return Private Alert attribute 'body'.
           *
           * This function is used by the Alerter to access the body of
           * a particular Alert to be displayed in the MainWindow.
           */
        std::string getAlertBody();
        /**
           * @name Alert time getter.
           * @brief Gets the private Alert attribute 'alertTime'.
           * @return Private Alert attribute 'body'.
           *
           * This function is used by the Alerter to access the time of
           * a particular Alert to be displayed in the MainWindow.
           */
        QDateTime getAlertTime();
};
#endif
