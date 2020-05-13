#ifndef CS_PROJECT_DATE_H
#define CS_PROJECT_DATE_H
#include <iostream>
#include "../Time/time.h"
using namespace std;




class Date{
private:
    int day, month, year;
    Time time;
public:
    void set_day(const int &d);
    int get_day() const;
    void set_month(const int &m);
    int get_month() const;
    void set_year(const int &y);
    int get_year() const;
    bool equal_date(const Date &d2) const &;
    bool operator ==(const Date &d2) const &;
    bool compare_date(const Date &d2) const &;
    bool operator >(const Date &d2) const &;
    bool operator <(const Date &d2) const &;

    string Date_to_string() const &;
    Date(){
        day=01, month=01, year=1970;
    };
    ~Date()= default;
};

#endif //CS_PROJECT_DATE_H
