#include <string>
#include <QDateTime>

#include "alert.h"

Alert::Alert(std::string descr, QDateTime time)
{
    alertBody = descr;
    alertTime = time;
}

Alert::~Alert() {}

void Alert::setAlertBody(std::string body)
{
    alertBody = body;
}

void Alert::setAlertTime(QDateTime time)
{
    alertTime = time;
}

std::string Alert::getAlertBody()
{
    return alertBody;
}

QDateTime Alert::getAlertTime()
{
    return alertTime;
}
