#ifndef CS_PROJECT_TIME_H
#define CS_PROJECT_TIME_H
#include <iostream>
using namespace std;

class Time{
private:
    int hours, minutes, seconds;
public:
    void set_hours(const int &h);
    int get_hours() const;
    void set_minutes(const int &m);
    int get_minutes() const;
    void set_seconds(const int &s);
    int get_seconds() const;

    void set_time(const int &h, const int &m, const int &s);
    void set_time(const string &time);

    int tot_seconds() const;
    int tot_mins() const;
    bool equal_sec(Time t2) const &;
    bool operator ==(Time t2) const &;
    bool equal_min(Time t2) const &;
    bool operator > (Time t2) const &;
    bool operator < (Time t2) const &;
    Time(){
        hours=0, minutes=0, seconds=0;
    };
    ~Time()=default;
};


#endif //CS_PROJECT_TIME_H
