//
// Created by carlt on 08/05/20.
//

#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../../utility.h"
#include "../Date/Date.h"
#include "../Time/Time.h"

struct list_int{ string key; int val; };
struct list_float{ string key; float val; };
struct list_char{ string key; char val; };
struct list_string{ string key; string val; };
struct list_date{ string key; Date val; };
struct list_time{ string key; Time val; };

class Row{
public:
    string key;
    vector<list_int> ints;
    vector<list_float> floats;
    vector<list_char> chars;
    vector<list_string> texts;
    vector<list_date> dates;
    vector<list_time> times;
};


class Table {
private:
    string name;
    vector<string> elements;
    Row defaultrow;
    vector<Row> rows;
public:
    void get_data(string in);
    void empty_unused_elements();
    Table(string in);
};
#endif //CS_PROJECT_TABLE_H
