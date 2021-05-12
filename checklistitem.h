#ifndef CHECKLISTITEM_H
#define CHECKLISTITEM_H

#include <string>

#include "lockable.h"

class ChecklistItem : public Lockable
{
private:
    std::string title;
    std::string body;

public:
    ChecklistItem();
    ~ChecklistItem();

    void setTitle(std::string);
    void setBody(std::string);

    std::string getTitle();
    std::string getBody();
};

#endif // CHECKLISTITEM_H
