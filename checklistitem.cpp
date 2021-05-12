#include "checklistitem.h"

ChecklistItem::ChecklistItem() : Lockable()
{
    title = "";
    body = "";
}

ChecklistItem::~ChecklistItem() {}

void ChecklistItem::setTitle(std::string t)
{
    title = t;
}
void ChecklistItem::setBody(std::string b)
{
    body = b;
}

std::string ChecklistItem::getTitle()
{
    return title;
}

std::string ChecklistItem::getBody()
{
    return body;
}
