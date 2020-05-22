#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../Date/Date.h"
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
    static bool check_CREATE_syntax(string in, const bool &show_err=true);
    static vector<string> get_CREATE_data(string in);
    vector<void *> cols;
    vector<string> elementsTypes;
    vector<string> elementsNames;
public:
    void* create_col(string in);

public:
    explicit Table(const string &in);
    Table()=default;
    ~Table()=default;
    void set_name(string name){name=name;}
    string get_name(){return name;}
    void empty_table();
};
#endif //CS_PROJECT_TABLE_H
