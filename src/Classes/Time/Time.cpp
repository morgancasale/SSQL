#include "Time.h"
using namespace std;

unsigned int c_counter(const string & in, char char_to_count){
    int counter=0;
    for(char c:in){
        if(c==char_to_count) counter++;
    }
    return counter;
}

void Time::set_hours(const int &h) {
    if(h<0 or h>24){
        cerr<<endl<<"Hours format error"<<endl;
    } else{ hours=h; }
}
unsigned int Time::get_hours() const { return hours; }
void Time::set_minutes(const int &m) {
    if(m<0 or m>60){
        cerr<<endl<<"Minutes format error"<<endl;
    }
    else{ minutes=m; }
}
unsigned int Time::get_minutes() const { return minutes; }
void Time::set_seconds(const int &s) {
    if(s<0 or s>60){
        cerr<<endl<<"Seconds format error"<<endl;
    }
    else{ seconds=s; }
}
unsigned int Time::get_seconds() const { return seconds; }

void Time::set_time(const int &h, const int &m, const int &s) {
    set_hours(h);
    set_minutes(m);
    set_seconds(s);
}

void Time::set_time(const string &time) {
    char sub=' ';
    bool err=false;
    unsigned int tmp;
    if((tmp=c_counter(time, ':')) == 1 or tmp == 2){
        sub=':';
    }
    else if((tmp=c_counter(time, '.')) == 1 or tmp == 2){
        sub='.';
    }
    else{
        cerr<<"Time data format error!"<<endl;
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


unsigned int Time::tot_seconds() const {
    return 3600*hours+60*minutes+seconds;
}
unsigned int Time::tot_mins() const {
    return 60*hours+minutes;
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