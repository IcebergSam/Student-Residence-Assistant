#include <string>
#include <QDateTime>

#include "calevent.h"

CalEvent::CalEvent(QObject *parent)
    : QObject(parent), Lockable() {}

CalEvent::~CalEvent() {}

void CalEvent::setStarttime(QDateTime t)
{
    starttime = t;
}

void CalEvent::setDescription(std::string d)
{
    description = d;
}

QDateTime CalEvent::getStarttime()
{
    return starttime;
}

std::string CalEvent::getDescription()
{
    return description;
}
