#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../../utility.h"
#include "../Date/Date.h"
#include "../Time/Time.h"

using namespace std;

template<typename type> class Column{
public:
    vector<type> values;
    string key;
    bool not_null;
};

class Table{
private:
    string name;
    vector<string> elementsTypes;
    vector<string> elementsNames;
    vector<void *> cols;
public:
    void* create_col(const string &in);

public:
    explicit Table(const string &in);
    Table()=default;
    void Table2(const string &in);
    ~Table()=default;
    string get_name(){return name;}
};
#endif //CS_PROJECT_TABLE_H
