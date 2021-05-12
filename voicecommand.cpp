#include "voicecommand.h"
#include "LanguageParser.h"
#include <QDebug>
#include <QString>

VoiceCommand::VoiceCommand(QObject *parent) : QObject(parent) {}

VoiceCommand::~VoiceCommand() {}

void VoiceCommand::receive_command(QString naturalLang)
{
    LanguageParser::Command command = LanguageParser::parseCommand(naturalLang.toStdString());

    bool error = false;
if(command.target == "timer"){
    switch(command.action){
        case LanguageParser::ACTIONS::CREATE:
        case LanguageParser::ACTIONS::START:
            if(command.param1Type == LanguageParser::COMPLEMENT_TYPE::TIME_LEN) {   //Might cause problems
                emit create_timer(command.param1, "New Timer"); //QString::fromStdString(command.param3));
            } else { error = true; return; }
            break;
        case LanguageParser::ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
} else if ( command.target == "appointment" || command.target == "event" || command.target == "reminder" ){
    switch(command.action){
        case LanguageParser::ACTIONS::CREATE:
            if(command.dayOfWeek != LanguageParser::DAY_OF_WEEK::NO_DATE) {
                emit create_calendarEvent(LanguageParser::dowToInt(command.dayOfWeek), QString::fromStdString(command.param3));
            } else { error = true; }
            break;
        case LanguageParser::ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
} else if(command.target == "note"){
    switch(command.action){
        case LanguageParser::ACTIONS::CREATE:
            if(command.param3Type == LanguageParser::COMPLEMENT_TYPE::TEXT) {
                emit create_note(QString::fromStdString(command.param3));
            } else { error = true; }
            break;
        case LanguageParser::ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
} else if(command.target == "studytimer"){
    switch(command.action){
        case LanguageParser::ACTIONS::CREATE:
            if(command.param1Type == LanguageParser::COMPLEMENT_TYPE::TIME_LEN) {
                emit create_studytimer(command.param1, "Keep Studying!"); //QString::fromStdString(command.param3));
            } else { error = true; return; }
            break;
        case LanguageParser::ACTIONS::EDIT:
            break;
        case LanguageParser::ACTIONS::START:
            break;
        default:
            error = true;
    }
} else if(command.target == "checklist"){
    switch(command.action){
        case LanguageParser::ACTIONS::CREATE:
        if(command.param3Type == LanguageParser::COMPLEMENT_TYPE::TEXT) {
            emit create_checklistItem(QString::fromStdString(command.param3));
        } else { error = true; }
            break;
        case LanguageParser::ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
}
if(error){
    //--TODO: Throw some error here--
}
}
