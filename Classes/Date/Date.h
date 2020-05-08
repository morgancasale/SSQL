#ifndef CS_PROJECT_DATE_H
#define CS_PROJECT_DATE_H
#include <iostream>
using namespace std;

class Date{
public:
    int day, month, year;
    bool compare_Date(const Date &term) const;
    string Date_to_string();
    Date(){
        day=01, month=01, year=1970;
    };
    ~Date()= default;
};


#endif //CS_PROJECT_DATE_H
