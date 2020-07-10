#include "Time.h"
using namespace std;

int c_counter(const string & in, char char_to_count){
    int counter=0;
    for(char c:in){
        if(c==char_to_count) counter++;
    }
    return counter;
}

void Time::set_hours(const int &h) {
    try{
        if(h<0 or h>24){
            throw("Hours format error");
        }
        else{
            hours=h;
        }
    }
    catch(const string &e){
        cerr<<endl<<e;
    }
}
int Time::get_hours() const { return hours; }
void Time::set_minutes(const int &m) {
    try{
        if(m<0 or m>60){
            throw("Minutes format error");
        }
        else{
            minutes=m;
        }
    }
    catch(const string &e){
        cerr<<endl<<e;
    }
}
int Time::get_minutes() const { return minutes; }
void Time::set_seconds(const int &s) { try{
        if(s<0 or s>60){
            throw("Seconds format error");
        }
        else{
            seconds=s;
        }
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
    int a;
    if((a=c_counter(time,':'))==1 or a==2){
        sub=':';
    }
    else if((a=c_counter(time,'.'))==1 or a==2){
        sub='.';
    }
    else{
        cerr<<"Time data format error";
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

int Time::tot_seconds() const {
    return 3600*hours+60*minutes+seconds;
}
int Time::tot_mins() const {
    return 3600*hours+60*minutes;
}

bool Time::equal_sec(Time t2) const & { return this->tot_seconds()==t2.tot_seconds(); }
bool Time::operator==(Time t2) const & { return equal_sec(t2); }
bool Time::equal_min(Time t2) const & { return this->tot_mins()==t2.tot_mins(); }

bool Time::operator>(Time t2) const & { return this->tot_seconds()>t2.tot_seconds(); }
bool Time::operator<(Time t2) const & { return this->tot_seconds()<t2.tot_seconds(); }
bool Time::operator>=(Time t2) const & { return (this->tot_seconds()>t2.tot_seconds() or equal_sec(t2)); }
bool Time::operator<=(Time t2) const & { return (this->tot_seconds()<t2.tot_seconds() or equal_sec(t2)); }

string Time::to_string() const{
    string tmp;
    if(seconds!=0){
        tmp=std::to_string(hours)+":"+std::to_string(minutes)+":"+std::to_string(seconds);
    }
    else{
        tmp=std::to_string(hours)+":"+std::to_string(minutes);
    }
    return tmp;
}