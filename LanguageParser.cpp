#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "LanguageParser.h"

/*
void LanguageParser::initCustomTargets(){
    LanguageParser::customCommandTargets = std::vector<std::string>();
}
*/

//This does not support decimals in the form of "and xx hundredths". Only digit construction supported after decimal point.
long double LanguageParser::parseNumber(std::string number, const bool& isTime, size_t* _oldPos){
    //This is gonna be a lot of ifs because English numbers are funky.

    if(number.back()!=' '){
        number.push_back(' ');
    }

    long double intNum=0, actingNum=0;
    int negativeMultiplier=1;

    /* usingDigitConstruction codes:
     * -1: number has been detected to not use digit construction
     *  0: unsure
     *  1: primed (depending on what follows this number uses digit construction)
     *  2: using digit construction (user is listing off digits)
     *  3: Now working with decimals (only digit construction supported)
     */
    int usingDigitConstruction=0;
    bool x10Waiting=false;
    bool consecutive100=false;
    int currentMagnitude=40;
    bool usedTimeWords=false;
    bool beginsWithZero=false;

    size_t pos=0, oldPos=(_oldPos!=nullptr? *_oldPos: 0);

    std::string word;
    bool error=false; //If this is true, then we found a word we couldn't parse or the number the user said doesn't make sense.
    while((pos=number.find(' ', oldPos))!=std::string::npos){
        word=number.substr(oldPos, pos - oldPos);

        //std::cout <<"  word: " << word << std::endl;
        if(word=="zero" || word=="oh" || word=="o"){
            if(intNum==0 && actingNum==0){ beginsWithZero=true; }
            usingDigitConstruction=2; //"0" is only ever said when listing off digits
            actingNum=actingNum * 10;
            x10Waiting=false;
        }else if(word=="one" || word=="a"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 1;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=1;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 1;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=1;
                }
            }
            x10Waiting=false;
        }else if(word=="two" || word=="to" || word=="too"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 2;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=2;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 2;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=2;
                }
            }
            x10Waiting=false;
        }else if(word=="three"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 3;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=3;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 3;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=3;
                }
            }
            x10Waiting=false;
        }else if(word=="four"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 4;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=4;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 4;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=4;
                }
            }
            x10Waiting=false;
        }else if(word=="five"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 5;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=5;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 5;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=5;
                }
            }
            x10Waiting=false;
        }else if(word=="six"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 6;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=6;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 6;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=6;
                }
            }
            x10Waiting=false;
        }else if(word=="seven"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 7;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=7;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 7;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=7;
                }
            }
            x10Waiting=false;
        }else if(word=="eight"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 8;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=8;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 8;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=8;
                }
            }
            x10Waiting=false;
        }else if(word=="nine"){
            if(usingDigitConstruction >= 2){
                if(!x10Waiting){
                    actingNum=actingNum * 10 + 9;
                    if(usingDigitConstruction==3){ currentMagnitude-=1; }
                }else{
                    actingNum+=9;
                }
            }else{
                if(usingDigitConstruction==1){
                    usingDigitConstruction=2;
                    actingNum=actingNum * 10 + 9;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=9;
                }
            }
            x10Waiting=false;
        }else if(word=="ten"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 10;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 10;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=10;
                }
            }
            x10Waiting=false;
        }else if(word=="eleven"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 11;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 11;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=11;
                }
            }
            x10Waiting=false;
        }else if(word=="twelve"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 12;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 12;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=12;
                }
            }
            x10Waiting=false;
        }else if(word=="thirteen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 13;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 13;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=13;
                }
            }
            x10Waiting=false;
        }else if(word=="fourteen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 14;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 14;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=14;
                }
            }
            x10Waiting=false;
        }else if(word=="fifteen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 15;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 15;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=15;
                }
            }
            x10Waiting=false;
        }else if(word=="sixteen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 16;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 16;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=16;
                }
            }
            x10Waiting=false;
        }else if(word=="seventeen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 17;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 17;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=17;
                }
            }
            x10Waiting=false;
        }else if(word=="eighteen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 18;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 18;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=18;
                }
            }
            x10Waiting=false;
        }else if(word=="nineteen"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 19;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 19;
                }else{
                    if(usingDigitConstruction==0){ usingDigitConstruction=1; }
                    actingNum+=19;
                }
            }
            x10Waiting=false;
        }else if(word=="twenty"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 20;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 20;
                }else{
                    actingNum+=20;
                }
            }
            x10Waiting=true;
        }else if(word=="thirty"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 30;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 30;
                }else{
                    actingNum+=30;
                }
            }
            x10Waiting=true;
        }else if(word=="forty"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 40;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 40;
                }else{
                    actingNum+=40;
                }
            }
            x10Waiting=true;
        }else if(word=="fifty"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 50;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 50;
                }else{
                    actingNum+=50;
                }
            }
            x10Waiting=true;
        }else if(word=="sixty"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 60;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 60;
                }else{
                    actingNum+=60;
                }
            }
            x10Waiting=true;
        }else if(word=="seventy"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 70;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 70;
                }else{
                    actingNum+=70;
                }
            }
            x10Waiting=true;
        }else if(word=="eighty"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 80;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 80;
                }else{
                    actingNum+=80;
                }
            }
            x10Waiting=true;
        }else if(word=="ninety"){
            if(usingDigitConstruction >= 2){
                actingNum=actingNum * 100 + 90;
                if(usingDigitConstruction==3){ currentMagnitude-=2; }
            }else{
                if(x10Waiting || usingDigitConstruction==1){
                    if(usingDigitConstruction==-1){ error=true; }
                    usingDigitConstruction=2;
                    actingNum=actingNum * 100 + 90;
                }else{
                    actingNum+=90;
                }
            }
            x10Waiting=true;
        }else if(word=="hundred"){
            if(x10Waiting || consecutive100 || usingDigitConstruction >= 2){
                error=true;
            }else{
                if(actingNum >= 10 && intNum!=0){
                    error=true;
                }else{
                    actingNum*=100;
                }
            }
            x10Waiting=false;
            consecutive100=true;
            usingDigitConstruction=-1;
        }else if(word=="thousand"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 3){
                intNum+=actingNum * std::pow(10, 3);
                actingNum=0;
                currentMagnitude=3;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="million"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 6){
                intNum+=actingNum * std::pow(10, 6);
                actingNum=0;
                currentMagnitude=6;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="billion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 9){
                intNum+=actingNum * std::pow(10, 9);
                actingNum=0;
                currentMagnitude=9;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="trillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 12){
                intNum+=actingNum * std::pow(10, 12);
                actingNum=0;
                currentMagnitude=12;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="quadrillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 15){
                intNum+=actingNum * std::pow(10, 15);
                actingNum=0;
                currentMagnitude=15;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="quintillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 18){
                intNum+=actingNum * std::pow(10, 18);
                actingNum=0;
                currentMagnitude=18;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="sextillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 21){
                intNum+=actingNum * std::pow(10, 21);
                actingNum=0;
                currentMagnitude=21;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="septillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 24){
                intNum+=actingNum * std::pow(10, 24);
                actingNum=0;
                currentMagnitude=24;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="octillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 27){
                intNum+=actingNum * std::pow(10, 27);
                actingNum=0;
                currentMagnitude=27;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="nonillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 30){
                intNum+=actingNum * std::pow(10, 30);
                actingNum=0;
                currentMagnitude=30;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="decillion"){
            if(usingDigitConstruction==3){
                intNum+=actingNum * (std::pow(10, currentMagnitude));
                actingNum=0;
            }else if(currentMagnitude > 33){
                intNum+=actingNum * std::pow(10, 33);
                actingNum=0;
                currentMagnitude=33;
            }else{
                error=true;
            }
            x10Waiting=false;
            consecutive100=false;
            usingDigitConstruction=-1;
        }else if(word=="and" || word=="n" || word=="nd"){
            //do nothing here, ignore it
        }else if(word=="point"){
            intNum+=actingNum;
            actingNum=0;
            usingDigitConstruction=3;
            currentMagnitude=0;
            x10Waiting=false;
            consecutive100=false;
        }else if(word=="negative"){
            if(intNum==0 && actingNum==0 && negativeMultiplier==1){
                negativeMultiplier=-1;
            }else{
                error=true;
            }
        }else if(isTime && (word=="hour" || word=="hours" || word=="minute" || word=="minutes" || word=="second" || word=="seconds")){
            //std::cout << "    actingNum= " << std::to_string(actingNum) << std::endl;
            //std::cout << "    intNum= " << std::to_string(intNum) << std::endl;
            usedTimeWords=true;
            if(word=="hour" || word=="hours"){
                actingNum+=intNum;
                if(actingNum >= 100 && actingNum <= 2400){
                    intNum=(floor(actingNum / 100) * 60 + fmod(actingNum, 100)) * 60; //--TODO: MAYBE THIS LINE IS A BIT WRONG--
                }else if(actingNum > 2400){
                //}else if(actingNum > 2400 || actingNum > 24){
                    //Guards against both setting over 24 hours and asking for a time over 24:00=00:00
                    error=true;
                }else{
                    intNum=actingNum * 60 * 60;
                }
            }else if(word=="minute" || word=="minutes"){
                actingNum+=intNum;
                intNum=actingNum * 60;
            }else if(word=="second" || word=="seconds"){
                intNum+=actingNum;
            }
            actingNum=0;
        }else if(isTime && (word=="AM" || word=="PM")){
            //std::cout << "    actingNum= " << std::to_string(actingNum) << std::endl;
            //std::cout << "    intNum= " << std::to_string(intNum) << std::endl;
            usedTimeWords=true;
            if(actingNum >= 0 && actingNum < 60){
                if(beginsWithZero){
                    //It's minutes and the input was meant to be "00:xx"
                    intNum=actingNum * 60;
                }else{
                    intNum=actingNum * 60 * 60;
                }
                actingNum = 0;
            }else if(actingNum >= 100 && actingNum < 6060){
                intNum=(floor(actingNum / 100) * 60 + fmod(actingNum, 100)) * 60;
            }else if(actingNum >= 10000 && actingNum < 240000){
                intNum=(floor(actingNum / 10000) * 60 + floor(fmod(actingNum, 10000) / 100)) * 60 + fmod(actingNum, 100);
            }else{
                error=true;
            }
            if(word=="AM"){
                intNum+=actingNum;
            }else if(word=="PM"){
                intNum+=actingNum + (12 * 60 * 60);
            }
            actingNum=0;
            break; //--TODO: Will this cause problems?--
        }else{
            //Specifically don't update oldPos so we can parse the word again after.
            break;
        }

        //std::cout << "  actingNum= " << std::to_string(actingNum) << std::endl;
        //std::cout << "  intNum= " << std::to_string(intNum) << std::endl;
        if(error){ break; }
        oldPos=pos + 1;
    }

    if(isTime && !usedTimeWords){
        usedTimeWords=true;
        //std::cout << "    actingNum= " << std::to_string(actingNum) << std::endl;
        //std::cout << "    intNum= " << std::to_string(intNum) << std::endl;
        if(actingNum >= 0 && actingNum < 60){
            if(beginsWithZero){
                //It's minutes and the input was meant to be "00:xx"
                intNum=actingNum * 60;
            }else{
                intNum=actingNum * 60 * 60;
            }
            actingNum = 0;
        }else if(actingNum >= 100 && actingNum < 6060){
            intNum=(floor(actingNum / 100) * 60 + fmod(actingNum, 100)) * 60;
        }else if(actingNum >= 10000 && actingNum < 240000){
            intNum=(floor(actingNum / 10000) * 60 + floor(fmod(actingNum, 10000) / 100)) * 60 + fmod(actingNum, 100);
        }else{
            error=true;
        }
        intNum+=actingNum;
        actingNum=0;
    }

    if(error){ throw std::invalid_argument("Number not understood"); }
    if(currentMagnitude < 0){
        actingNum*=(std::pow(10, currentMagnitude));
    }
    intNum+=actingNum;

    if(_oldPos!=nullptr){ *_oldPos=oldPos; }
    return intNum * negativeMultiplier;
}


LanguageParser::Command LanguageParser::parseCommand(std::string command){
    //Once again a lot of if statements because English
    //A laughable parody of natural language comprehension but I'm only one person and we never really promised natural language comprehension in the first place

    /* KNOWN ISSUES:
     * Will NOT behave correctly when complement of "to" or "that" phrases contains words checked for in wordMatchesComplementStart() when "to" or "that" is not the last complement.
     * Using "o'clock" or a variant will cause an error.
     */

    if(command.back()!=' '){
        command.push_back(' ');
    }

    ACTIONS action;
    std::string target;
    long double complement1, complement2;
    std::string complement3;
    COMPLEMENT_TYPE complement1Type = COMPLEMENT_TYPE::EMPTY, complement2Type = COMPLEMENT_TYPE::EMPTY, complement3Type = COMPLEMENT_TYPE::EMPTY;
    DAY_OF_WEEK dayOfWeek = DAY_OF_WEEK::NO_DATE;
    bool lookingForNumber = false;

    if(command.empty()){ throw std::invalid_argument("Empty command"); }

    size_t pos=0, oldPos=0;
    std::string word;
    bool error=false; //If this is true, then we found a word we couldn't parse or the command the user said doesn't make sense.
    std::string errorMessage="Command not understood or unsupported command";
    if((pos=command.find(' ', oldPos))!=std::string::npos){ //The first word of a command is always the action.
        word=command.substr(oldPos, pos - oldPos);
        //std::cout << word << std::endl;
        if(word=="make" || word=="set" || word=="create" || word=="add"){
            action=ACTIONS::CREATE;
        }else if(word=="delete" || word=="remove"){
            //action=ACTIONS::DELETE; //Turns out this is a lot harder than we thought
            action=ACTIONS::BADACTION;
            error=true;
            errorMessage = "Unsupported command";
        }else if(word=="edit"){
            action=ACTIONS::EDIT;
        }else if(word=="start"){
            action=ACTIONS::START;
        }else if(word=="stop" || word=="cancel"){
            //action=ACTIONS::STOP; //Also hard to implement
            action=ACTIONS::BADACTION;
            error=true;
            errorMessage = "Unsupported command";
        }else if(word=="remind"){
            action=ACTIONS::REMIND;
        }else{
            action=ACTIONS::BADACTION;
            error=true;
        }
        oldPos=pos + 1;
    }else{
        action=ACTIONS::BADACTION;
        error=true;
    }
    //Next while loop to parse the target.
    if(action!=ACTIONS::REMIND){ //"remind" action implies the target is a reminder.
        while((pos=command.find(' ', oldPos))!=std::string::npos && !error){
            word=command.substr(oldPos, pos - oldPos);
            //std::cout << word << std::endl;
            if(LanguageParser::wordMatchesSkippable(word)){
                //This is the ignore list. To begin, we can ignore all determiners since a command system doesn't care about them.
                oldPos=pos + 1;
            }else{
                try{
                    target=LanguageParser::matchCommandTarget(command, &oldPos);
                }catch(const std::invalid_argument& e){
                    error=true;
                    errorMessage=e.what();
                }
                oldPos=pos + 1;
                break;
            }
        }
    }else{
        target="reminder";
    }
    //std::cout << "Target set: " << target << std::endl;
    //Next while loop to parse first complement.
    while((pos=command.find(' ', oldPos))!=std::string::npos && !error){
        word=command.substr(oldPos, pos - oldPos);
        //std::cout << word << std::endl;
        if(LanguageParser::wordMatchesSkippable(word) || word == "on"){
            //This is the ignore list. To begin, we can ignore all determiners since a command system doesn't care about them.
            //Turns out we also don't care about the word "on"
        }else if(word=="at"){
            //Parse for time
            complement1Type = COMPLEMENT_TYPE::TIME_START;
            oldPos=pos + 1;
            try{
                complement1=LanguageParser::parseNumber(command, true, &oldPos);
            }catch(const std::invalid_argument& e){
                error=true;
                errorMessage=e.what();
            }
            continue; //! parseNumber sets oldPos to just before the next word, so we can parse it here next.
        }else if(word=="from"){
            //Parse for time
            complement1Type = COMPLEMENT_TYPE::TIME_END;
            oldPos=pos + 1;
            try{
                complement1=LanguageParser::parseNumber(command, true, &oldPos);
            }catch(const std::invalid_argument& e){
                error=true;
                errorMessage=e.what();
            }
            continue;
        }else if(word=="to"){
            //Check target for context: either time or VP[+inf]
            if(complement1Type == COMPLEMENT_TYPE::TIME_START && complement2Type != COMPLEMENT_TYPE::TIME_END){
                complement2Type = COMPLEMENT_TYPE::TIME_END;
                oldPos=pos + 1;
                try{
                    complement2=LanguageParser::parseNumber(command, true, &oldPos);
                }catch(const std::invalid_argument& e){
                    error=true;
                    errorMessage=e.what();
                }
                continue;
            }else{
                complement3Type = COMPLEMENT_TYPE::TEXT;
                complement3 = command.substr(pos+1, command.length()-pos-1);
                break;
            }
        }else if(word=="until" || word=="till"){
            //Parse for time
            complement2Type = COMPLEMENT_TYPE::TIME_END;
            oldPos=pos + 1;
            try{
                complement2=LanguageParser::parseNumber(command, true, &oldPos);
            }catch(const std::invalid_argument& e){
                error=true;
                errorMessage=e.what();
            }
            continue;
        }else if(word=="for"){
            //parse for time (relative)
            if(complement1Type == COMPLEMENT_TYPE::EMPTY){
                complement1Type=COMPLEMENT_TYPE::TIME_LEN;
                oldPos=pos + 1;
                try{
                    complement1=LanguageParser::parseNumber(command, true, &oldPos);
                }catch(const std::invalid_argument& e){
                    error=true;
                    errorMessage=e.what();
                }
            }else{
                //Allowing things like "create an appointment at 10PM for 3 hours"
                complement2Type=COMPLEMENT_TYPE::TIME_LEN;
                oldPos=pos + 1;
                try{
                    complement2=LanguageParser::parseNumber(command, true, &oldPos);
                }catch(const std::invalid_argument& e){
                    error=true;
                    errorMessage=e.what();
                }
            }
            continue;
        }else if(word=="in"){
            //parse for time (relative)
            complement1Type = COMPLEMENT_TYPE::TIME_REL;
            oldPos=pos + 1;
            try{
                complement1=LanguageParser::parseNumber(command, true, &oldPos);
            }catch(const std::invalid_argument& e){
                error=true;
                errorMessage=e.what();
            }
            continue;
        //}else if(word=="on"){
            //parse for date/time (half-absolute)
            //We actually don't care about "on", so it's now checked for with the rest of the ignore list.
        }else if(word=="that"){
            //parse for TP[+fin]
            complement3Type = COMPLEMENT_TYPE::TEXT;
            complement3 = command.substr(pos+1, command.length()-pos-1);
            break;
        }else if(LanguageParser::wordMatchesDayOfWeek(word) != DAY_OF_WEEK::NO_DATE){
            dayOfWeek = LanguageParser::wordMatchesDayOfWeek(word);
            lookingForNumber = true;
        }else if(lookingForNumber && !LanguageParser::wordMatchesComplementStart(word)){
            //! There is a chance that we're looking for a time now
            lookingForNumber = false;
            complement1Type = COMPLEMENT_TYPE::TIME_START; //! If no complement start specified, then this is "[day of week] [time]" with implied "at"
            oldPos=pos + 1;
            try{
                complement1=LanguageParser::parseNumber(command, true, &oldPos);
            }catch(const std::invalid_argument& e){
                error=true;
                errorMessage=e.what();
            }
            continue;
        }else{
            error=true;
        }

        if(error){ break; }
        oldPos=pos + 1;
    }
    if(error){ throw std::invalid_argument(errorMessage); }

    return (LanguageParser::Command){
        action,
        target,
        (int)std::lroundl(complement1),
        (int)std::lroundl(complement2),
        complement3,
        dayOfWeek,
        complement1Type,
        complement2Type,
        complement3Type
    };
}

void LanguageParser::executeCommand(const LanguageParser::Command& command){
    //--TODO: IMPLEMENT THIS!--
bool error = false;
if(command.target == "timer"){
    switch(command.action){
        case ACTIONS::CREATE:
        case ACTIONS::START:
            if(command.param1Type == COMPLEMENT_TYPE::TIME_LEN){
                std::cout << "create a timer for " << std::to_string(command.param1) << " seconds" << std::endl;
                //Create a timer for command.param1 seconds
            }else{ error = true; }
            break;
        case ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
}else if(command.target == "reminder"){
    switch(command.action){
        case ACTIONS::REMIND:
        case ACTIONS::CREATE:
            break;
        case ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
}else if(command.target == "appointment" || command.target == "event"){
    switch(command.action){
        case ACTIONS::CREATE:
            break;
        case ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
}else if(command.target == "note"){
    switch(command.action){
        case ACTIONS::CREATE:
            break;
        case ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
}else if(command.target == "study timer"){
    switch(command.action){
        case ACTIONS::CREATE:
            break;
        case ACTIONS::EDIT:
            break;
        case ACTIONS::START:
            break;
        default:
            error = true;
    }
}else if(command.target == "checklist"){
    switch(command.action){
        case ACTIONS::CREATE:
            break;
        case ACTIONS::EDIT:
            break;
        default:
            error = true;
    }
}
if(error){
    //--TODO: Throw some error here--
}
}

/**
 * Add string target to list of command targets to look for when parsing commands.
 * WARNING: This has undefined behaviour when you insert a target that begins with the full name of an existing target.
 * @param target
 * @return 1 if the target is already in the list (fail state), 0 otherwise (success)
 */
/*
int LanguageParser::addCommandTarget(const std::string& target, int numArgs){
   if(std::find(LanguageParser::commandTargets.begin(), LanguageParser::commandTargets.end(), target) != LanguageParser::commandTargets.end()){
       return 1;
   }
   if(std::find(LanguageParser::customCommandTargets.begin(), LanguageParser::customCommandTargets.end(), target) != LanguageParser::customCommandTargets.end()){
       return 1;
   }
   LanguageParser::customCommandTargets.push_back(target);
    return 0;
}
*/


std::string LanguageParser::matchCommandTarget(const std::string& command, size_t* oldPos){
    for(auto& commandTarget : LanguageParser::commandTargets){
        if(command.find(commandTarget, *oldPos)==*oldPos){
            *oldPos=commandTarget.length() + 1;
            return commandTarget;
        }
    }
    /*
    for(auto & commandTarget : LanguageParser::customCommandTargets) {
        if(command.find(commandTarget, *oldPos)==*oldPos){
            *oldPos=commandTarget.length() + 1;
            return commandTarget;
        }
    }
    */
    throw std::invalid_argument("Invalid target");
    return std::string();
}

bool LanguageParser::wordMatchesSkippable(const std::string& word){
    return word=="a" || word=="an" || word=="the" || word=="my" || word=="me" || word=="uh" || word=="um";
}

bool LanguageParser::wordMatchesComplementStart(const std::string& word){
    return word=="at" || word=="from" || word=="to" || word=="until" || word=="till" || word=="for" || word=="in" || word=="on" || word=="that";
}

LanguageParser::DAY_OF_WEEK LanguageParser::wordMatchesDayOfWeek(const std::string& word){
    if(word == "monday"){
        return DAY_OF_WEEK::MONDAY;
    }else if(word == "tuesday"){
        return DAY_OF_WEEK::TUESDAY;
    }else if(word == "wednesday"){
        return DAY_OF_WEEK::WEDNESDAY;
    }else if(word == "thursday"){
        return DAY_OF_WEEK::THURSDAY;
    }else if(word == "friday"){
        return DAY_OF_WEEK::FRIDAY;
    }else if(word == "saturday"){
        return DAY_OF_WEEK::SATURDAY;
    }else if(word == "sunday"){
        return DAY_OF_WEEK::SUNDAY;
    }else if(word == "tomorrow"){
        return DAY_OF_WEEK::TOMORROW;
    }else{
        return DAY_OF_WEEK::NO_DATE;
    }
}

int LanguageParser::dowToInt(DAY_OF_WEEK dow){
    switch(dow){
        case DAY_OF_WEEK::MONDAY:
            return 1;
        case DAY_OF_WEEK::TUESDAY:
            return 2;
        case DAY_OF_WEEK::WEDNESDAY:
            return 3;
        case DAY_OF_WEEK::THURSDAY:
            return 4;
        case DAY_OF_WEEK::FRIDAY:
            return 5;
        case DAY_OF_WEEK::SATURDAY:
            return 6;
        case DAY_OF_WEEK::SUNDAY:
            return 7;
        case DAY_OF_WEEK::TOMORROW:
            return 8;
        case DAY_OF_WEEK::NO_DATE:
            return -1;
    }
}
