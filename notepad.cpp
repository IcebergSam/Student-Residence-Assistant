#include <string>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>

#include "notepad.h"
#include "ui_notepad.h"
#include "note.h"
#include "noteeditor.h"

#include <QDebug>
Notepad::Notepad(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::setCurrentNItem(QListWidgetItem* nItem)
{
    currentNItem = nItem;
}

Note* Notepad::getNote(QListWidgetItem* nItem)
{
    auto it = noteWidgetMap.find(nItem);
    if (it != noteWidgetMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void Notepad::on_newButton_clicked()
{
    bool ok;
    QString inputtitle = QInputDialog::getText(0,"New Note",
            "Enter New Note Title", QLineEdit::Normal, QString(), &ok);

    if (!ok || inputtitle == "")
    {
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        return;
    }
    std::string inputtitle_str = inputtitle.toStdString();

    Note* newNote = new Note;
    newNote->setTitle(inputtitle_str);

    QListWidgetItem* nItem = new QListWidgetItem;
    nItem->setText(inputtitle);
    ui->listWidget->addItem(nItem);

    noteWidgetMap.insert({nItem, newNote});

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Lock Note",
                "Do you want to lock this note?", QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::Yes)
    {
        QString inputpswd = QInputDialog::getText(0,"Create password",
                "Enter password for this event:", QLineEdit::Normal, QString(), &ok);
        if (ok)
        {
            std::string inputpswd_str = inputpswd.toStdString();
            newNote->lock(inputpswd_str);
        }
        else
        {
            QMessageBox::information(0,"","Note not locked.");
        }
    }
    else
    {
        QMessageBox::information(0,"","Note not locked.");
    }

    NoteEditor edit(this, newNote);
    edit.exec();
}

void Notepad::on_editButton_clicked()
{
    bool ok;

    bool relock_after_edit = false;
    std::string pswd;

    if(getNote(currentNItem)->isLocked())
    {
        relock_after_edit = true;

        QString inputpswd = QInputDialog::getText(0,"Note Locked","Enter password:",
                                QLineEdit::Normal, QString(), &ok);

        std::string inputpswd_str = inputpswd.toStdString();
        if (!ok)
        {
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            return;
        }

        if (!(getNote(currentNItem)->unlock(inputpswd_str)))
        {
            QMessageBox::information(0,"","Incorrect Password.");
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            return;
        }
    }

    NoteEditor edit(this, getNote(currentNItem));
    edit.exec();

    if(relock_after_edit)
    {
        getNote(currentNItem)->lock();
    }
}

void Notepad::on_deleteButton_clicked()
{
    bool ok;

    bool relock_after_edit = false;
    std::string pswd;

    if(getNote(currentNItem)->isLocked())
    {
        relock_after_edit = true;

        QString inputpswd = QInputDialog::getText(0,"Note Locked","Enter password:",
                                QLineEdit::Normal, QString(), &ok);

        std::string inputpswd_str = inputpswd.toStdString();
        if (!ok)
        {
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            return;
        }

        if (!(getNote(currentNItem)->unlock(inputpswd_str)))
        {
            QMessageBox::information(0,"","Incorrect Password.");
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            return;
        }
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Note",
                "Are you sure you want to delete this note?",
                QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    Note* note = getNote(currentNItem);
    noteWidgetMap.erase(currentNItem);
    currentNItem->setHidden(true);

    delete note;
    delete currentNItem;

    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

void Notepad::on_listWidget_itemClicked(QListWidgetItem *item)
{
    setCurrentNItem(item);
    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);

}

void Notepad::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //open a read-only copy
    setCurrentNItem(item);
    NoteEditor edit(this, getNote(item), true);
    edit.exec();
}

void Notepad::editor_closed()
{
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

void Notepad::voice_create_note(QString body)
{
    // create a new note
}
