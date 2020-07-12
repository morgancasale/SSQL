#ifndef CS_PROJECT_TIME_H
#define CS_PROJECT_TIME_H
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

//remove char sub from string then returns a stringstream from the modified input string
stringstream data_ss(string in, const char &sub){
    replace(in.begin(), in.end(), sub, ' ');
    stringstream ss(in);
    return ss;
}


class Time{
private:
    unsigned int hours, minutes, seconds;
public:
    void set_hours(const int &h);
    unsigned int get_hours() const;
    void set_minutes(const int &m);
    unsigned int get_minutes() const;
    void set_seconds(const int &s);
    unsigned int get_seconds() const;

    void set_time(const int &h, const int &m, const int &s);
    void set_time(const string & time);

    unsigned int tot_seconds() const;
    unsigned int tot_mins() const;
    bool equal_sec(Time t2) const &;
    bool operator ==(Time t2) const &;
    bool equal_min(Time t2) const &;
    bool operator > (Time t2) const &;
    bool operator < (Time t2) const &;
    bool operator >= (Time t2) const &;
    bool operator <= (Time t2) const &;
    string to_string() const;
    Time(){
        hours=0, minutes=0, seconds=0;
    };
    Time(const string & in){
        set_time(in);
    }
    ~Time()=default;
};
#endif //CS_PROJECT_TIME_H