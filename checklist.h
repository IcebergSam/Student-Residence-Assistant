#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <string>
#include <QDialog>
#include <QListWidgetItem>

#include "checklistitem.h"

namespace Ui {
class Checklist;
}

class Checklist : public QDialog
{
    Q_OBJECT

private:
    Ui::Checklist *ui;
    QListWidgetItem* currentNItem;

    std::map<QListWidgetItem*, ChecklistItem*> checklistItemWidgetMap;

    /**
     * @name currentNItem setter
     * @brief Sets currentNItem to the given QListWidgetItem.
     * @return Void.
     *
     * Sets the pointer to the current checklist item to point to the given QListWidgetItem.
     */
    void setCurrentNItem(QListWidgetItem*);
    /**
     * @name Current Selected Checklist Getter
     * @brief Returns a pointer to the currently-selected ChecklistItem.
     * @return A pointer to the currently-selected ChecklistItem.
     *
     * Returns a pointer to the currently-selected ChecklistItem.
     */
    ChecklistItem* getItem(QListWidgetItem*);

public:
    explicit Checklist(QWidget *parent = nullptr);
    ~Checklist();

private slots:
    /**
     * @name New Checklist
     * @brief Creates a new checklist.
     * @return Void.
     *
     * This method triggers when the New button is pressed in the checklist interface, and creates a new checklist on execution.
     */
    void on_newButton_clicked();
    /**
     * @name Edit Checklist
     * @brief Opens the checklist item editor with the selected checklist.
     * @return Void.
     *
     * This method triggers when the Edit button is pressed in the checklist interface, and opens the checklist item editor with the selected checklist.
     */
    void on_editButton_clicked();
    /**
     * @name Lock Checklist
     * @brief Locks the selected checklist.
     * @return Void.
     *
     * This method triggers when the Lock button is pressed in the checklist interface. Prompts the user if they would like to lock the selected,
     * checklist, and locks it if confirmed.
     */
    void on_lockButton_clicked();
    /**
     * @name Unlock Checklist
     * @brief Unlocks the selected checklist.
     * @return Void.
     *
     * This method triggers when the Unlock button is pressed in the checklist interface. Prompts the user if they would like to unlock the selected,
     * checklist, and unlocks it if confirmed.
     */
    void on_unlockButton_clicked();
    /**
     * @name Delete Checklist
     * @brief Deletes the selected checklist.
     * @return Void.
     *
     * This method triggers when the Delete button is pressed in the checklist interface. Prompts the user if they would like to delete the selected
     * checklist, and deletes it if confirmed.
     */
    void on_deleteButton_clicked();
    /**
     * @name Mark Checklist as Finished
     * @brief Marks the selected checklist as finished.
     * @return Void.
     *
     * This method triggers when the Finish button is pressed in the checklist interface. Prompts the user if they would like to mark the selected
     * checklist as finished, and marks it as finished if confirmed.
     */
    void on_finishButton_clicked();
    /**
     * @name Mark Checklist as Unfinished
     * @brief Marks the selected checklist as unfinished.
     * @return Void.
     *
     * This method triggers when the Unfinish button is pressed in the checklist interface. Prompts the user if they would like to mark the selected
     * checklist as unfinished, and marks it as unfinished if confirmed.
     */
    void on_unfinishButton_clicked();
    void on_upButton1_clicked();
    void on_downButton1_clicked();
    void on_upButton2_clicked();
    void on_downButton2_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget2_itemClicked(QListWidgetItem *item);
    void on_listWidget2_itemDoubleClicked(QListWidgetItem *item);

public slots:
    /**
     * @name Editor Closing Tasks
     * @brief Performs tasks required to happen when the editor is closed.
     * @return Void.
     *
     * This method triggers when the checklist editor is closed. Temporarily disables all buttons in the editor.
     */
    void editor_closed();
    /**
     * @name Automated Checklist Creator
     * @brief Creates a checklist based on the provided QString.
     * @return Void.
     *
     * Creates a checklist based on the provided QString, without looking for user input. Meant for use with voice commands.
     */
    void voice_create_item(QString);
};

#endif
