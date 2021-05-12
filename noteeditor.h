#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QDialog>

#include "notepad.h"
#include "note.h"

namespace Ui {
class NoteEditor;
}

class NoteEditor : public QDialog
{
    Q_OBJECT

private:
    Ui::NoteEditor* ui;
    Note* currentNote;

public:
    explicit NoteEditor(Notepad*, Note*, bool readonly=false);
    ~NoteEditor();

private slots:
    /**
     * @name Save Note
     * @brief Saves the changes to the note.
     * @return Void.
     *
     * This method triggers when the Save button is pressed in the note interface.
     */
    void on_saveButton_clicked();
    /**
     * @name Cancel Saving Changes to Note
     * @brief Discards the changes to the note.
     * @return Void.
     *
     * This method triggers when the Cancel button is pressed in the note interface.
     */
    void on_cancelButton_clicked();

signals:
    void done_editing();
};

#endif // NOTEEDITOR_H
