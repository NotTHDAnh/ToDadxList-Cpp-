#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <time.h>
#pragma once

using namespace std;

class Calendar{
private:
    time_t t; 
    tm *now;
public:
    Calendar(){
        t = time(0);
        now = localtime(&t);
    }

    time_t getDay(){
        return now->tm_mday;
    }

    time_t getMonth(){
        return now->tm_mon + 1;
    }

    time_t getYear(){
        return now->tm_year + 1900;
    }
    bool Earlier(string deadline){
        tm tm = {};
        istringstream ss(deadline);
        ss >> get_time(&tm, "%d/%m/%Y");
        if(getYear() > tm.tm_year + 1900){
            return 1;
        }
        else if(getYear() == tm.tm_year + 1900 && getMonth() > tm.tm_mon + 1){
            return 1;
        }
        else if(getYear() == tm.tm_year + 1900 && getMonth() == tm.tm_mon + 1 && getDay() > tm.tm_mday){
            return 1;
        }
        else return 0;
    }

    bool Today(string deadline){
        tm tm = {};
        istringstream ss(deadline);
        ss >> get_time(&tm, "%d/%m/%Y");
        return (now->tm_year == tm.tm_year && now->tm_mon == tm.tm_mon && now->tm_mday == tm.tm_mday);
    }

    bool Tomorrow(string deadline){
        tm tm = {};
        istringstream ss(deadline);
        ss >> get_time(&tm, "%d/%m/%Y");

        std::tm tomorrow = *now;
        tomorrow.tm_mday += 1;
        mktime(&tomorrow);

        return(tm.tm_year == tomorrow.tm_year && tm.tm_mon == tomorrow.tm_mon && tm.tm_mday == tomorrow.tm_mday);

        return 0;
    }

    string countHowManyDaysTillDeadline(string deadline){
        tm tm = {};
        istringstream ss(deadline);
        ss >> get_time(&tm, "%d/%m/%Y");

        if(getYear() > tm.tm_year + 1900){
            return "Your task is overdue";
        }
        else if(getYear() == tm.tm_year + 1900 && getMonth() > tm.tm_mon + 1){
            return "Your task is overdue";
        }
        else if(getYear() == tm.tm_year  + 1900 && getMonth() == tm.tm_mon + 1 && getDay() > tm.tm_mday){
            return "Your task is overdue";
        }
        else{
            int time_left;
            string Announcement; 
            if(getYear() < tm.tm_year + 1900){
                time_left = 1900 + tm.tm_year - getYear();
                Announcement += "years";
            }
            else if(getMonth() < tm.tm_mon + 1){
                time_left = tm.tm_mon - getMonth() + 1;
                Announcement += "months";
            }
            else {
                time_left = tm.tm_mday - getDay();
                Announcement += "days";
            }
            Announcement = to_string(time_left) + " " + Announcement + " left";
            return Announcement;
        }
    }
};


