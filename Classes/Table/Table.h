#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
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
    int primaryKey_index;
public:
    bool find_check_primaryKey(const string & in);
    bool create_col(string in);

    vector<string> elementsTypes;
    vector<void *> cols;
    vector<string> elementsNames;
public:
    bool set_Table(const string &in);
    Table()=default;
    ~Table()=default;
    void set_name(string name_in){name=name_in;}
    string get_name(){ return name; }
    void empty_table();

    int find_col_by_name(const string & in);

    bool check_key(const string & in);

    bool check_type(const string & type);


};
#endif //CS_PROJECT_TABLE_H
