#ifndef EDITEVENTDIALOG_H
#define EDITEVENTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QListWidgetItem>

#include "calendar.h"
//#include "alerttime.h"

namespace Ui {
class EditEventDialog;
}

class EditEventDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::EditEventDialog* ui;
    QDateTime* eventTime = new QDateTime;

public:
    explicit EditEventDialog(Calendar*);
    ~EditEventDialog();

private slots:
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_pushButton_clicked();

signals:
    void pushButton_clicked(QDateTime*);

};

#endif // EDITEVENTDIALOG_H
