#include <string>
#include <QString>

#include "ui_noteeditor.h"
#include "noteeditor.h"
#include "notepad.h"

NoteEditor::NoteEditor(Notepad* parent, Note* note, bool readonly)
: QDialog(), ui(new Ui::NoteEditor)
{
    ui->setupUi(this);
    currentNote = note;

    QString s = QString::fromStdString(currentNote->getBody());
    ui->textEdit->insertPlainText(s);

    if(readonly)
    {
        ui->textEdit->setReadOnly(true);
        ui->saveButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);
    }

    connect(this, &NoteEditor::done_editing, parent, &Notepad::editor_closed);
}

NoteEditor::~NoteEditor()
{
    delete ui;
}

void NoteEditor::on_saveButton_clicked()
{
    QString saved_text = ui->textEdit->toPlainText();
    std::string saved_str = saved_text.toStdString();

    currentNote->setBody(saved_str);

    emit done_editing();
    this->close();
}

void NoteEditor::on_cancelButton_clicked()
{
    emit done_editing();
    this->close();
}
