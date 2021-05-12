#ifndef VOICECOMMAND_H
#define VOICECOMMAND_H

#include <QObject>
#include <QString>
#include <string>

#include "timer.h"
#include "studytimer.h"
#include "notepad.h"
#include "checklist.h"
#include "calendar.h"
#include "LanguageParser.h"

class VoiceCommand : public QObject
{
    Q_OBJECT

public:
    explicit VoiceCommand(QObject *parent = nullptr);
    ~VoiceCommand();

signals:
    void create_timer(int, QString);
    void create_studytimer(int, QString);
    void create_note(QString);
    void create_checklistItem(QString);
    void create_calendarEvent(int, QString);

public slots:
    void receive_command(QString);

};

#endif // VOICECOMMAND_H
