#ifndef CALEVENTOPTION_H
#define CALEVENTOPTION_H

#include <QObject>
#include <QDialog>
#include <QListWidgetItem>

#include "calendar.h"

namespace Ui {
class CalEventOption;
}

class CalEventOption : public QDialog
{
    Q_OBJECT

private:
    Ui::CalEventOption* ui;
    QListWidgetItem* cItem;

public:
    explicit CalEventOption(Calendar*, QListWidgetItem*);
    ~CalEventOption();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void delete_selected(QListWidgetItem*);
    void edit_selected(QListWidgetItem*);

};

#endif // CALEVENTOPTION_H
