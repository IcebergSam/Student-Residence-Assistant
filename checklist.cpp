#include <string>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>

#include "checklist.h"
#include "ui_checklist.h"
#include "checklistitem.h"
#include "checklistitemeditor.h"

#include <QDebug>
Checklist::Checklist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Checklist)
{
    ui->setupUi(this);
    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);
}

Checklist::~Checklist()
{
    delete ui;
}

void Checklist::setCurrentNItem(QListWidgetItem* nItem)
{
    currentNItem = nItem;
}

ChecklistItem* Checklist::getItem(QListWidgetItem* nItem)
{
    auto it = checklistItemWidgetMap.find(nItem);
    if (it != checklistItemWidgetMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void Checklist::on_newButton_clicked()
{
    bool ok;

    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    QString inputtitle = QInputDialog::getText(0,"New Item",
            "Enter New Item Title", QLineEdit::Normal, QString(), &ok);

    if (!ok || inputtitle == "")
    {
        return;
    }

    std::string inputtitle_str = inputtitle.toLocal8Bit().constData();

    ChecklistItem* newItem = new ChecklistItem();
    newItem->setTitle(inputtitle_str);

    QListWidgetItem* nItem = new QListWidgetItem;
    nItem->setText(inputtitle);
    ui->listWidget->addItem(nItem);

    checklistItemWidgetMap.insert({nItem, newItem});

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Lock Item",
                "Do you want to lock this item?", QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::Yes)
    {
        QString inputpswd = QInputDialog::getText(0,"Create password",
                "Enter password for this event:", QLineEdit::Normal, QString(), &ok);
        if (ok)
        {
            std::string inputpswd_str = inputpswd.toLocal8Bit().constData();
            newItem->lock(inputpswd_str);
        }
        else
        {
            QMessageBox::information(0,"","Item not locked.");
        }
    }
    else
    {
        QMessageBox::information(0,"","Item not locked.");
    }

    ChecklistItemEditor edit(this, newItem);
    edit.exec();
}

void Checklist::on_lockButton_clicked() {
    bool ok;

    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Lock Item",
                "Do you want to lock this item?", QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::Yes)
    {
        QString inputpswd = QInputDialog::getText(0,"Create password",
                "Enter password for this event:", QLineEdit::Normal, QString(), &ok);
        if (ok)
        {
            std::string inputpswd_str = inputpswd.toLocal8Bit().constData();
            ChecklistItem* newItem = getItem(currentNItem);
            newItem->lock(inputpswd_str);
        }
        else
        {
            QMessageBox::information(0,"","Item not locked.");
        }
    }
    else
    {
        QMessageBox::information(0,"","Item not locked.");
    }
}

void Checklist::on_unlockButton_clicked() {
    bool ok;

    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Unlock Item",
                "Do you want to unlock this item?", QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::Yes)
    {
        QString inputpswd = QInputDialog::getText(0,"Item Locked","Enter password:",
                                QLineEdit::Normal, QString(), &ok);

        if (ok)
        {
            std::string inputpswd_str = inputpswd.toLocal8Bit().constData();
            if (!(getItem(currentNItem)->unlock(inputpswd_str)))
            {
                QMessageBox::information(0,"","Incorrect Password.");
            }
            else {
                QMessageBox::information(0,"","Item unlocked.");
            }
        }
        else {
            QMessageBox::information(0,"","Unlock Item Failed");
        }
    }

    else {
        QMessageBox::information(0,"","Action cancelled");
    }
}

void Checklist::on_editButton_clicked()
{
    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    ChecklistItemEditor edit(this, getItem(currentNItem));
    edit.exec();
}

void Checklist::on_deleteButton_clicked()
{
    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Item",
                "Are your sure you want to delete this item?",
                QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    ChecklistItem* item = getItem(currentNItem);
    checklistItemWidgetMap.erase(currentNItem);
    currentNItem->setHidden(true);

    delete item;
    delete currentNItem;
}

void Checklist::on_finishButton_clicked()
{
    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Mark Finished",
                "Are your sure you want to mark it as finished?",
                QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    int row = ui->listWidget->currentRow();
    ui->listWidget2->addItem(ui->listWidget->takeItem(row));
}

void Checklist::on_unfinishButton_clicked()
{
    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Mark Unfinished",
                "Are your sure you want to mark it as unfinished?",
                QMessageBox::Yes | QMessageBox:: No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    int row = ui->listWidget2->currentRow();
    ui->listWidget->addItem(ui->listWidget2->takeItem(row));
}

void Checklist::on_upButton1_clicked()
{
    int currentRow = ui->listWidget->currentRow();
    int previousRow = currentRow - 1;
    QListWidgetItem *temp = ui->listWidget->takeItem(previousRow);
    ui->listWidget->insertItem(previousRow, currentNItem);
    ui->listWidget->insertItem(currentRow, temp);
}

void Checklist::on_downButton1_clicked()
{
    int currentRow = ui->listWidget->currentRow();
    int nextRow = currentRow + 1;
    QListWidgetItem *temp = ui->listWidget->takeItem(nextRow);
    ui->listWidget->insertItem(nextRow, currentNItem);
    ui->listWidget->insertItem(currentRow, temp);
}

void Checklist::on_upButton2_clicked()
{
    int currentRow = ui->listWidget2->currentRow();
    int previousRow = currentRow - 1;
    QListWidgetItem *temp = ui->listWidget2->takeItem(previousRow);
    ui->listWidget2->insertItem(previousRow, currentNItem);
    ui->listWidget2->insertItem(currentRow, temp);
}

void Checklist::on_downButton2_clicked()
{
    int currentRow = ui->listWidget2->currentRow();
    int nextRow = currentRow + 1;
    QListWidgetItem *temp = ui->listWidget2->takeItem(nextRow);
    ui->listWidget2->insertItem(nextRow, currentNItem);
    ui->listWidget2->insertItem(currentRow, temp);
}

void Checklist::on_listWidget_itemClicked(QListWidgetItem *item)
{
    setCurrentNItem(item);

    if(getItem(currentNItem)->isLocked())
    {
        ui->lockButton->setEnabled(false);
        ui->unlockButton->setEnabled(true);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->finishButton->setEnabled(false);
        ui->unfinishButton->setEnabled(false);
        ui->upButton1->setEnabled(true);
        ui->downButton1->setEnabled(true);
        ui->upButton2->setEnabled(false);
        ui->downButton2->setEnabled(false);
    }
    else {
        ui->lockButton->setEnabled(true);
        ui->unlockButton->setEnabled(false);
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->finishButton->setEnabled(true);
        ui->unfinishButton->setEnabled(false);
        ui->upButton1->setEnabled(true);
        ui->downButton1->setEnabled(true);
        ui->upButton2->setEnabled(false);
        ui->downButton2->setEnabled(false);
    }
}

void Checklist::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //open a read-only copy
    setCurrentNItem(item);
    ChecklistItemEditor edit(this, getItem(item), true);
    edit.exec();
}

void Checklist::on_listWidget2_itemClicked(QListWidgetItem *item)
{
    setCurrentNItem(item);

    if(getItem(currentNItem)->isLocked())
    {
        ui->lockButton->setEnabled(false);
        ui->unlockButton->setEnabled(true);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->finishButton->setEnabled(false);
        ui->unfinishButton->setEnabled(false);
        ui->upButton1->setEnabled(false);
        ui->downButton1->setEnabled(false);
        ui->upButton2->setEnabled(true);
        ui->downButton2->setEnabled(true);

    }
    else {
        ui->lockButton->setEnabled(true);
        ui->unlockButton->setEnabled(false);
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->finishButton->setEnabled(false);
        ui->unfinishButton->setEnabled(true);
        ui->upButton1->setEnabled(false);
        ui->downButton1->setEnabled(false);
        ui->upButton2->setEnabled(true);
        ui->downButton2->setEnabled(true);
    }
}

void Checklist::on_listWidget2_itemDoubleClicked(QListWidgetItem *item)
{
    //open a read-only copy
    setCurrentNItem(item);
    ChecklistItemEditor edit(this, getItem(item), true);
    edit.exec();
}

void Checklist::editor_closed()
{
    ui->lockButton->setEnabled(false);
    ui->unlockButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->finishButton->setEnabled(false);
    ui->unfinishButton->setEnabled(false);
    ui->upButton1->setEnabled(false);
    ui->downButton1->setEnabled(false);
    ui->upButton2->setEnabled(false);
    ui->downButton2->setEnabled(false);
}

void Checklist::voice_create_item(QString body)
{
   // create a new checklist item
}
