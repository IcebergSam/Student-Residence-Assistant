#ifndef SETINFO_H
#define SETINFO_H

#include <QDialog>

namespace Ui {
class SetInfo;
}

class SetInfo : public QDialog
{
    Q_OBJECT

public:
    explicit SetInfo(QWidget *parent = nullptr);
    ~SetInfo();

private:
    Ui::SetInfo *ui;
};

#endif // SETINFO_H
