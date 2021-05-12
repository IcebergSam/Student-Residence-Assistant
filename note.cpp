#include "note.h"

Note::Note() : Lockable()
{
    title = "";
    body = "";
}

Note::~Note() {}

void Note::setTitle(std::string t)
{
    title = t;
}
void Note::setBody(std::string b)
{
    body = b;
}

std::string Note::getTitle()
{
    return title;
}

std::string Note::getBody()
{
    return body;
}
