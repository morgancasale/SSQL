#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../../syntax.h"
#include <vector>
using namespace std;

template<typename type> class Column {
public:
    vector<type> values;
    string key;
    bool not_null=false;
    bool auto_increment=false;
};

class Table{
private:
    string name;
    static vector<string> get_CREATE_data(string in);
    int primaryKey_index;
    static int count_data(const vector<string> &data, const string &type);


public:
    bool find_check_primaryKey(const string & in);
    bool create_col(string in, const vector<string> & data);
    int rows=0;
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

    static bool check_type(const string & type);


    void cast_data_to_col(const int &col_i, const string &type, const string &data);

    void auto_increment_col();

    bool set_INSERT_INTO_data(const vector<string> &elements_Names, const vector<string> &elementsValues);

    bool check_INSERT_INTO_data(const vector<string> &filled_elements);

    int get_col_index(const string &in);

    bool find_Rows_by_value(const string &data, const int &col_i, vector<int> &foundRows);
};
#endif //CS_PROJECT_TABLE_H
