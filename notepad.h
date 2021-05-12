#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <string>
#include <QDialog>
#include <QListWidgetItem>

#include "note.h"

namespace Ui {
class Notepad;
}

class Notepad : public QDialog
{
    Q_OBJECT

private:
    Ui::Notepad *ui;
    QListWidgetItem* currentNItem;

    std::map<QListWidgetItem*, Note*> noteWidgetMap;

	/**
	 * @name currentNItem setter
	 * @brief Sets currentNItem to the given QListWidgetItem.
	 * @return Void.
	 *
	 * Sets the pointer to the current note item to point to the given QListWidgetItem.
	 */
    void setCurrentNItem(QListWidgetItem*);
	/**
	 * @name Current Selected Note Getter
	 * @brief Returns a pointer to the currently-selected Note.
	 * @return A pointer to the currently-selected Note.
	 *
	 * Returns a pointer to the currently-selected Note.
	 */
    Note* getNote(QListWidgetItem*);

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
	/**
	 * @name New Note
	 * @brief Creates a new note.
	 * @return Void.
	 *
	 * This method triggers when the New button is pressed in the notepad interface, and creates a new note on execution.
	 */
    void on_newButton_clicked();
	/**
	 * @name Edit Note
	 * @brief Opens the note item editor with the selected note.
	 * @return Void.
	 *
	 * This method triggers when the Edit button is pressed in the notepad interface, and opens the note editor with the selected note.
	 */
    void on_editButton_clicked();
	/**
	 * @name Delete Note
	 * @brief Deletes the selected note.
	 * @return Void.
	 *
	 * This method triggers when the Delete button is pressed in the notepad interface. Prompts the user if they would like to delete the selected
	 * note, and deletes it if confirmed.
	 */
    void on_deleteButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

public slots:
	/**
	 * @name Editor Closing Tasks
	 * @brief Performs tasks required to happen when the editor is closed.
	 * @return Void.
	 *
	 * This method triggers when the note editor is closed. Temporarily disables all buttons in the editor.
	 */
    void editor_closed();

	/**
	 * @name Automated Note Creator
	 * @brief Creates a note based on the provided QString.
	 * @return Void.
	 *
	 * Creates a note based on the provided QString, without looking for user input. Meant for use with voice commands.
	 */
    void voice_create_note(QString);
};

#endif // NOTEPAD_H
