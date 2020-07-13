#include "Time.h"
#define RED     "\033[31m"
#define RESET   "\033[0m"
using namespace std;

unsigned int c_counter(const string & in, char char_to_count){
    int counter=0;
    for(char c:in){
        if(c==char_to_count) counter++;
    }
    return counter;
}

bool Time::set_hours(const int &h) {
    bool noErr=true;
    if(h<0 or h>24){
        noErr=false;
        cout << RED<<endl<<"Hours format error"<<endl << RESET;
    } else{ hours=h; }
    return noErr;
}
unsigned int Time::get_hours() const { return hours; }
bool Time::set_minutes(const int &m) {
    bool noErr=true;
    if(m<0 or m>60){
        noErr=false;
        cout << RED<<endl<<"Minutes format error"<<endl << RESET;
    }
    else{ minutes=m; }
    return noErr;
}
unsigned int Time::get_minutes() const { return minutes; }
bool Time::set_seconds(const int &s) {
    bool noErr=true;
    if(s<0 or s>60){
        noErr=false;
        cout << RED<<endl<<"Seconds format error"<<endl << RESET;
    }
    else{ seconds=s; }
    return noErr;
}
unsigned int Time::get_seconds() const { return seconds; }

bool Time::set_time(const int &h, const int &m, const int &s) {
    return set_hours(h) and
    set_minutes(m) and
    set_seconds(s);
}

bool Time::set_time(const string &time) {
    char sub=' ';
    bool noErr=true;
    unsigned int tmp;
    if((tmp=c_counter(time, ':')) == 1 or tmp == 2){
        sub=':';
    }
    else if((tmp=c_counter(time, '.')) == 1 or tmp == 2){
        sub='.';
    }
    else{
        cout << RED<<"Time data format error!"<<endl << RESET;
        hours=0;
        minutes=0;
        seconds=42;
        noErr=false;
    }
    if(noErr){
        stringstream ss=data_ss(time, sub);
        ss>>hours>>minutes>>seconds;
    }
    return noErr;
}


unsigned int Time::tot_seconds() const {
    return 3600*hours+60*minutes+seconds;
}
unsigned int Time::tot_mins() const {
    return 60*hours+minutes;
}

bool Time::equal_sec(Time t2) const & { return this->tot_seconds()==t2.tot_seconds(); }
bool Time::operator==(Time t2) const & { return equal_sec(t2); }

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