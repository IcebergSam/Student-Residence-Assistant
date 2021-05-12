#ifndef CHECKLISTITEMEDITOR_H
#define CHECKLISTITEMEDITOR_H

#include <QDialog>

#include "checklist.h"
#include "checklistitem.h"

namespace Ui {
class ChecklistItemEditor;
}

class ChecklistItemEditor : public QDialog
{
    Q_OBJECT

private:
    Ui::ChecklistItemEditor* ui;
    ChecklistItem* thisitem;

public:
    explicit ChecklistItemEditor(Checklist*, ChecklistItem*, bool readonly=false);
    ~ChecklistItemEditor();

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

signals:
    void done_editing();
};

#endif // CHECKLISTITEMEDITOR_H
