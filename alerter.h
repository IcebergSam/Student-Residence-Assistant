#ifndef ALERTER_H
#define ALERTER_H

#include <QObject>
#include <string>
#include <vector>
#include <QThread>
#include <QMutex>
#include "alert.h"

/**
* @brief Class for sorting Alerts by time and comparing
*           Alert time with current local time.
* @author Sam Ahsan
*
* This class is run in a thread parallel to the main thread
* and shares a vector of Alert pointers with the main thread.
* It send a signal to the main thread containing a particular Alert
* when that Alert's time is equal to the current local time.
*/

class Alerter : public QObject
{
    Q_OBJECT

private:
    QMutex* mtx;
    bool exitThread;

        /**
           * @name alertsQueue sorter.
           * @brief Sorts a vector of pointers to Alerts by comparing their time values.
           * @param A std::vector of Alert pointers to be sorted.
           * @return A std::vector of Alert pointers sorted by time value.
           *
           * This method is used by Alerter to sort a copy of its alertsQueue and returns
           * a sorted copy of the (copy of) the Alerter's alertsQueue.
           */
    std::vector<Alert*> sortAlerts(std::vector<Alert*>);

public:
    /**
       * @name Constructor.
       * @brief Alerter created with a reference to its parent QObject MainWindow.
       * @param QObject pointer to the Alerter creator to initialize the object, or
       *            a null pointer.
       *
       * Alerters are created during construction of the MainWindow, then moved to a thread
       * to run parallel to the main thread where the MainWindow resides. Memory for a pointer
       * to Alerter attribute std::vector is allocated on the heap.
       */
    explicit Alerter(QObject *parent = nullptr);
        /**
           * @name Destructor.
           * @brief Alerters are destroyed as per C++ destruction. Heap memory freed.
           *
           * Alerter member alertsQueue is deallocated.
           */
    ~Alerter();

        /**
           * @name Mutex getter.
           * @brief Gets the private Alerter attribute 'mtx'.
           * @param None.
           * @return Private Alerter attribute QMutex* mtx.
           *
           * This method is used by the MainWindow (from the Alerter's parent thread) to lock
           * and unlock the given Alerter's mutex, which is used by the parent thread when MainWindow
           * manipulate Alerts in the given Alerter's alertsQueue.
           */
    QMutex* getMutex();
        /**
           * @name Mutex setter.
           * @brief Sets the private Alerter attribute 'mtx'.
           * @param None.
           * @return Void.
           *
           * This method is used during construction of the MainWindow (from the Alerter's parent thread)
           * to give the Alerter a reference to a recently created QMutex shared by it's parent thread.
           */
    void setMutex(QMutex*);

    std::vector<Alert*>* alertsQueue = new std::vector<Alert*>;

        /**
           * @name alertsQueue inserter.
           * @brief Inserts a pointer to an Alert into the Alerter's alertsQueue member.
           * @param A pointer to the Alert to be inserted.
           * @return Void.
           *
           * This method is used by the Timer, StudyTimer, and Calendar classes when the respective class's
           * method involving creation of an Alert is required to be inserted into the Alerter's alertsQueue.
           */
    void addtoQueue(Alert*);
        /**
           * @name alertsQueue eraser.
           * @brief Erases a pointer to an Alert from the Alerter's alertsQueue member.
           * @param A pointer to the Alert to be erased and a pointer to the std::vector from which to erase.
           * @return Void.
           *
           * This method is used by Alerter to remove an alert from the alertsQueue after it has been displayed;
           * or else used by the Timer, StudyTimer, and Calendar classes when the respective class's method
           * involving deletion of an Alert is required to be removed from the Alerter's alertsQueue.
           */
    void removefromQueue(Alert*, std::vector<Alert*>*);

signals:
        /**
           * @name Display signal.
           * @brief Sends a signal to the main thread to display the given Alert.
           * @param A pointer to the Alert to be displayed.
           * @return Void.
           *
           * This method is a signal used to notify the MainWindow that the given Alert is required to be displayed.
           * (Graphics in Qt cannot be updated from anywhere other than the main thread.)
           */
    void alert(Alert*);

public slots:
        /**
           * @name Alert listener.
           * @brief Sort the alertsQueue as Alerts are added and determine if they should be displayed.
           * @param A pointer to a specific instance of an Alerter's alertsQueue. .
           * @return Void.
           *
           * This method is initiated by a signal from the MainWindow. It runs a loop until a signal is received by
           * the Alerter indicating that the MainWindow will close and that the Alerter's thread should respond to a
           * request for it to cease execution when interrupted.
           */
    void waitForAlert(std::vector<Alert*>*);
        /**
           * @name Loop terminator.
           * @brief Sets the loop's execution condition to false).
           * @param Void.
           * @return Void.
           *
           * This method is initiated by a signal from the MainWindow. The condition for running the Alert listener loop
           * is a negation of the private attribute of the Alerter 'exitThread', which is set to true upon receving this signal.
           */
    void exit_thread();
};

#endif // ALERTER_H
