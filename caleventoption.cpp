#include <QListWidgetItem>

#include "ui_caleventoption.h"
#include "caleventoption.h"
#include "calendar.h"

CalEventOption::CalEventOption(Calendar* parent, QListWidgetItem* cListItem)
    : QDialog(), ui(new Ui::CalEventOption)
{
    ui->setupUi(this);

    cItem = cListItem;
    connect(this, &CalEventOption::delete_selected, parent, &Calendar::delete_selected);
    connect(this, &CalEventOption::edit_selected, parent, &Calendar::edit_selected);
}

CalEventOption::~CalEventOption()
{
    delete ui;
}

void CalEventOption::on_pushButton_clicked()
{
    emit delete_selected(cItem);
    this->close();
}

void CalEventOption::on_pushButton_2_clicked()
{
    emit edit_selected(cItem);
    this->close();
}
