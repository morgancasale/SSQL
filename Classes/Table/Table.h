#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../../utility.h"
#include "../Date/Date.h"
#include "../Time/Time.h"

struct list_int{ string key; int val; bool not_null=false; };
struct list_float{ string key; float val; bool not_null=false; };
struct list_char{ string key; char val; bool not_null=false; };
struct list_string{ string key; string val; bool not_null=false; };
struct list_date{ string key; Date val; bool not_null=false; };
struct list_time{ string key; Time val; bool not_null=false; };

class Row{
public:
    string key;
    vector<list_int> ints;
    vector<list_float> floats;
    vector<list_char> chars;
    vector<list_string> texts;
    vector<list_date> dates;
    vector<list_time> times;

    ~Row()=default;
};


class Table {
private:
    string name;
    vector<string> elements;
    string *primaryKey; //needs to be a pointer to a string
    Row defaultRow;
    vector<Row> rows;
public:
    string get_name(){return name;}

    void get_data(string in);
    void empty_unused_elements();
    Table(string in);

    ~Table()=default;
};
#endif //CS_PROJECT_TABLE_H
