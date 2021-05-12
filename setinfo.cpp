#include "setinfo.h"
#include "ui_setinfo.h"

SetInfo::SetInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetInfo)
{
    ui->setupUi(this);
}

SetInfo::~SetInfo()
{
    delete ui;
}
