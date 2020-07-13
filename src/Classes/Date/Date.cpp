#include "Date.h"

bool Date::equal_date(const Date &d2) const{
    bool response=false;
    if(this->get_day()==d2.get_day() and this->get_month()==d2.get_month() and this->get_year()==d2.get_year()){
        response=true;
    }
    return response;
}
bool Date::operator ==(const Date &d2) const &{ return equal_date(d2); }

bool Date::is_bigger_than(const Date &d2) const {
    bool bigger=false;
    if(this->get_year()>d2.get_year()){
        bigger=true;
    }else if(this->get_year()==d2.get_year()){
        if(this->get_month()>d2.get_month()){
            bigger=true;
        }else if(this->get_month()==d2.get_month()){
            bigger = this->get_day() > d2.get_day();
        }
    }
    return bigger;
}
bool Date::operator >(const Date &d2) const &{ return is_bigger_than(d2); }
bool Date::operator <(const Date &d2) const &{ return !is_bigger_than(d2); }
bool Date::operator >=(const Date &d2) const &{ return (is_bigger_than(d2) or equal_date(d2)); }
bool Date::operator <=(const Date &d2) const &{ return (!is_bigger_than(d2) or equal_date(d2)); }

bool Date::set_day(const int &d) {
    bool day_err=false;
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(d<0 or d>31){
                day_err=true;
            }
        break;
        case 2:
            if(d<0 or d>28+(1-abs(year)%4)){ //this account also for leap years
                day_err=true;
            }
        break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(d<0 or d>30){
                day_err=true;
            }
        break;
    }
    if(!day_err){
        day=d;
    }
    else{
        cout << RED<<"Day not valid!"<<endl << RESET;
    }
    return !day_err;
}
int Date::get_day() const { return day; }

bool Date::set_month(const int &m) {
    bool noErr=true;
    if(m>0 and m<=12){
        month=m;
    }
    else{
        noErr=false;
        cout << RED<<"Month not valid!"<<endl << RESET;
    }
    return noErr;
}
int Date::get_month() const{ return month; }

void Date::set_year(const int &y) { year=y; if(year<0){ AC=true; } }
int Date::get_year() const{ return year; }

string Date::date_to_string() const &{
    string d, m, y;
    d = (day < 10) ? ("0"+to_string(day)) : to_string(day);
    m = (month < 10) ? ("0"+to_string(month)) : to_string(month);
    y = to_string(abs(year));
    if(abs(year) < 1000){
        if(abs(year) < 100){
            if(abs(year) < 10){
                y = "000" + y;
            }else y = "00" + y;
        }else y = "0" + y;
    }
    if(AC){ return d + "-" + m + "-" + y +"AC";}
    return d + "-" + m + "-" + y;
}
bool Date::set_Date(const string & in){
    bool noErr=true;
    char sub;

    if(in.find('-')!=-1){
        sub='-';
    } else if(in.find('.')!=-1){
        sub='.';
    } else if(in.find('/')!=-1){
        sub='/';
    } else{
        noErr=false;
    }

    if(noErr){
        stringstream ss=data_ss(in, sub);
        int d, m, y;
        ss>>d>>m>>y;
        noErr=( set_day(d) and set_month(m) );
        if(noErr){
            set_year(y);
        }
    }

    if(!noErr){
        cout <<RED<<endl<<"An error occurred while creating the Date object!"<<endl << RESET;
    }
    return noErr;
}