#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../Date/Date.h"
#include "../../syntax.h"
#include <vector>
using namespace std;

template<typename type> class Column{
public:
    vector<type> values;
    string key;
    bool not_null;
    bool auto_increment;
};

class Table{
private:
    string name;
    static vector<string> get_CREATE_data(string in);
    vector<void *> cols;
    vector<string> elementsNames;
public:
    void* create_col(string in);

    vector<string> elementsTypes;
public:
    explicit Table(const string &in);
    Table()=default;
    ~Table()=default;
    void set_name(string name){name=name;}
    string get_name(){return name;}
    void empty_table();

    int find_col_by_name(const string &in);
};
#endif //CS_PROJECT_TABLE_H
