#ifndef NOTE_H
#define NOTE_H

#include <string>

#include "lockable.h"

class Note : public Lockable
{
private:
    std::string title;
    std::string body;

public:
    Note();
    ~Note();

    /**
     * @name Title Setter
     * @brief Sets the note title to the given string.
     * @param t The new title of the note.
     * @return Void.
     *
     * Sets the note title to the given string.
     */
    void setTitle(std::string t);
    /**
     * @name Body Setter
     * @brief Sets the note body to the given string.
     * @param t The new body of the note.
     * @return Void.
     *
     * Sets the note body to the given string.
     */
    void setBody(std::string b);

    /**
     * @name Title Getter
     * @brief Returns the title of the note.
     * @return The title of the note.
     *
     * Returns the title of the note.
     */
    std::string getTitle();
    /**
     * @name Body Getter
     * @brief Returns the body of the note.
     * @return The body of the note.
     *
     * Returns the body of the note.
     */
    std::string getBody();
};

#endif // NOTE_H
