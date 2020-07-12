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
//Getters and Setters:

    string to_string() const; //get_time
    bool set_time(const int &h, const int &m, const int &s);
    bool set_time(const string & time);

    bool set_hours(const int &h);
    unsigned int get_hours() const;

    bool set_minutes(const int &m);
    unsigned int get_minutes() const;

    bool set_seconds(const int &s);
    unsigned int get_seconds() const;
    unsigned int tot_seconds() const;
    unsigned int tot_mins() const;

    //Operators
    bool equal_sec(Time t2) const &;
    bool operator ==(Time t2) const &;
    bool operator > (Time t2) const &;
    bool operator < (Time t2) const &;
    bool operator >= (Time t2) const &;
    bool operator <= (Time t2) const &;
    Time(){
        hours=0, minutes=0, seconds=0;
    };
    Time(const string & in){
        set_time(in);
    }
    ~Time()=default;
};
#endif //CS_PROJECT_TIME_H