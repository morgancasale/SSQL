#ifndef CS_PROJECT_DATE_H
#define CS_PROJECT_DATE_H
#include <iostream>
#include "../Time/Time.h"
using namespace std;

class Date{
private:
    int day, month, year;
    bool AC=false;
public:
    bool set_day(const int &d);
    int get_day() const;
    bool set_month(const int &m);
    int get_month() const;
    void set_year(const int &y);
    int get_year() const;
    bool equal_date(const Date &d2) const;
    bool operator ==(const Date &d2) const &;
    bool is_bigger_than(const Date &d2) const ;
    bool operator >(const Date &d2) const &;
    bool operator <(const Date &d2) const &;
    bool operator <=(const Date &d2) const &;
    bool operator >=(const Date &d2) const &;
    string date_to_string() const &;
    Date(){
        day=01, month=01, year=1970;
    };
    ~Date()= default;

    bool set_Date(const string & in);
    Date(const string & in){
        if(!set_Date(in)){
            Date();
        }
    }
};

#endif //CS_PROJECT_DATE_H