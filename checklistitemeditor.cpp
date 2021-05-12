#include <string>
#include <QString>

#include "ui_checklistitemeditor.h"
#include "checklistitemeditor.h"
#include "checklist.h"

ChecklistItemEditor::ChecklistItemEditor(Checklist* parent, ChecklistItem* item, bool readonly)
: QDialog(), ui(new Ui::ChecklistItemEditor)
{
    ui->setupUi(this);

    thisitem = item;

    QString s = QString::fromUtf8(thisitem->getBody().c_str());
    ui->textEdit->insertPlainText(s);
    if(readonly)
    {
        ui->textEdit->setReadOnly(true);
    }

    connect(this, &ChecklistItemEditor::done_editing, parent, &Checklist::editor_closed);
}

ChecklistItemEditor::~ChecklistItemEditor()
{
    delete ui;
}

void ChecklistItemEditor::on_saveButton_clicked()
{
    QString saved_text = ui->textEdit->toPlainText();
    std::string str = saved_text.toLocal8Bit().constData();
    thisitem->setBody(str);
    emit done_editing();
    this->close();
}

void ChecklistItemEditor::on_cancelButton_clicked()
{
    emit done_editing();
    this->close();
}
