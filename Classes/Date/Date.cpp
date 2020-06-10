#include "Date.h"

bool Date::equal_date(const Date &d2) const &{
    bool response=false;
    if(this->get_day()==d2.get_day() and this->get_month()==d2.get_month() and this->get_year()==d2.get_year()){
        response=true;
    }
    return response;
}
bool Date::operator ==(const Date &d2) const &{ return equal_date(d2); }

bool Date::compare_date(const Date &d2) const &{
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
bool Date::operator >(const Date &d2) const &{ return compare_date(d2); }
bool Date::operator <(const Date &d2) const &{ return !compare_date(d2); }

void Date::set_day(const int &d) {
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
        cerr<<"Day not valid";
    }
}
int Date::get_day() const { return day; }

void Date::set_month(const int &m) {
    if(m>0 and m<=12){
        month=m;
    }
    else{
        cerr<<"Month not valid";
    }
}
int Date::get_month() const{ return month; }

void Date::set_year(const int &y) { year=y; if(year<0){ AC=true; } }
int Date::get_year() const{ return year; }

string Date::Date_to_string() const &{
    if(AC){ return to_string(day)+"-"+to_string(month)+"-"+to_string(abs(year))+"AC";}
    return to_string(day)+"-"+to_string(month)+"-"+to_string(year);
}
void Date::set_Date(const string & in){
    bool err=false;
    char sub;

    if(in.find(':')!=-1){
        sub=':';
    } else if(in.find('.')!=-1){
        sub='.';
    } else if(in.find('/')!=-1){
        sub='/';
    } else{
        err=true;
    }

    if(!err){
        stringstream ss=data_ss(in, sub);
        int d, m, y;
        ss>>d>>m>>y;
        set_day(d);
        set_month(m);
        set_year(y);
    } else{
        cerr<<endl<<"No date was found in this string!";
    }
}