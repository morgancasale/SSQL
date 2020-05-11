#include "Time.h"
using namespace std;
const exception time_error= (const exception &) "Time format error";

int Time::tot_seconds() const {
    return 360*hours+60*minutes+seconds;
}
int Time::tot_mins() const {
    return 360*hours+60*minutes;
}

void Time::set_hours(const int &h) {
    try{
        if(h>=0 and h<=24){
            throw("Hours format error");
        }
        hours=h;
    }
    catch(const string &e){
        cerr<<endl<<e;
    }
}
int Time::get_hours() const { return hours; }
void Time::set_minutes(const int &m) {
    try{
        if(m>=0 and m<=60){
            throw("Minutes format error");
        }
        minutes=m;
    }
    catch(const string &e){
        cerr<<endl<<e;
    }
}
int Time::get_minutes() const { return minutes; }
void Time::set_seconds(const int &s) { try{
        if(s>=0 and s<=60){
            throw("Seconds format error");
        }
        seconds=s;
    }
    catch(const string &e){
        cerr<<endl<<e;
    }
}
int Time::get_seconds() const { return seconds; }

void Time::set_time(const int &h, const int &m, const int &s) {
    set_hours(h);
    set_minutes(m);
    set_seconds(s);
}

void Time::set_time(const string &time) {
    char sub=' ';
    bool err=false;
    if(time.find(':')!=-1){
        sub=':';
    }
    else if(time.find('.')!=-1){
        sub='.';
    }
    else if(time.find(' ')!=-1){
    }
    else{
        cerr<<"time data format error";
        hours=0;
        minutes=0;
        seconds=42;
        err=true;
    }
    if(!err){
        stringstream ss=data_ss(time, sub);
        ss>>hours>>minutes>>seconds;
    }
}
