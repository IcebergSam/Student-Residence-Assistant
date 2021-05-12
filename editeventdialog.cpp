#include <QListWidgetItem>

#include "ui_editeventdialog.h"
#include "editeventdialog.h"
#include "calendar.h"

EditEventDialog::EditEventDialog(Calendar* parent)
    : QDialog(), ui(new Ui::EditEventDialog)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());

   connect(this, &EditEventDialog::pushButton_clicked, parent, &Calendar::timeEdited);
}

EditEventDialog::~EditEventDialog()
{
    delete ui;
}

void EditEventDialog::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->pushButton->setEnabled(true);

    *eventTime = dateTime;
}

void EditEventDialog::on_pushButton_clicked()
{
    emit pushButton_clicked(eventTime);
    this->close();
}
