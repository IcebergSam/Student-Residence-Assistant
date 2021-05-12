#include <QMessageBox>
#include <QString>
#include <QMutex>
#include <QDateTime>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <windows.h>

#include "alerter.h"
#include "alert.h"

Alerter::Alerter(QObject *parent) : QObject(parent) {}

Alerter::~Alerter()
{
    delete alertsQueue;
}

void Alerter::setMutex(QMutex *m)
{
    mtx = m;
}

QMutex* Alerter::getMutex()
{
    return mtx;
}

std::vector<Alert*> Alerter::sortAlerts(std::vector<Alert*> aQ)
{
    for (int i=0; i < (int)aQ.size()-1; i++)
    {
        for (int j=i+1; j < (int)aQ.size(); j++)
        {
            if (aQ[i]->getAlertTime().secsTo(aQ[j]->getAlertTime()) < 0)
            {
                Alert* tmp = aQ[i];
                aQ[i] = aQ[j];
                aQ[j] = tmp;
            }
        }
    }

    return aQ;
}

void Alerter::addtoQueue(Alert* newAlert)
{
    alertsQueue->push_back(newAlert);
}

void Alerter::removefromQueue(Alert* oldAlert, std::vector<Alert*>* aQ)
{
    aQ->erase(std::find(aQ->begin(), aQ->end(), oldAlert));
}

void Alerter::waitForAlert(std::vector<Alert*>* aQ)
{
    exitThread = false;

    std::vector<Alert*> ready;
    QDateTime now;

    Alert* nextAlert;
    QDateTime nextTime;

    while(!exitThread)
    {
        if (QThread::currentThread()->isInterruptionRequested())
        {
            return;
        }

        bool acquired = false;
        while(!acquired)
        {
            if(mtx->try_lock())
            {
                acquired = true;
                ready = *aQ;
                mtx->unlock();
            }
        }

        if(ready.size()>0)
        {
            ready = sortAlerts(ready);
			nextAlert = ready[0];

            nextTime = nextAlert->getAlertTime();
            now = QDateTime::currentDateTime();

            if (nextTime.date().year() == now.date().year() &&
                nextTime.date().month() == now.date().month() &&
                nextTime.date().day() == now.date().day() &&
                nextTime.time().hour() == now.time().hour() &&
                nextTime.time().minute() == now.time().minute() &&
                nextTime.time().second() == now.time().second() )
            {
                emit alert(nextAlert);
                sleep(1);

                bool acquired = false;
                while(!acquired)
                {
                    if(mtx->try_lock())
                    {
                        acquired = true;
                        removefromQueue(nextAlert, aQ);
                        mtx->unlock();
                    }
                }
            }
        }
		sleep(1);
    }
}

void Alerter::exit_thread()
{
    exitThread = true;
}
