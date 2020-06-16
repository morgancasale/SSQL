#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../../syntax.h"
#include <vector>
#include <fstream>
using namespace std;

template<typename type> class Column {
public:
    vector<type> values;
    vector<bool> valuesNullity;
    string key;
    bool not_null=false;
    bool auto_increment=false;
    ~Column()=default;
    void printCol_to_file(ofstream & out);
};

class Table{
private:
    string name;

    int primaryKey_index;

    static vector<string> get_CREATE_data(string in);
    static int count_data(const vector<string> &data, const string &type);

public:
    int rows=0;
    vector<string> elementsNames;
    vector<string> elementsTypes;
    vector<void *> cols;

    bool find_check_primaryKey(const string & in);
    bool create_col(string in, const bool &key_existence);
    void clear_col(const int &i);

    bool set_Table(const string &in);
    Table()=default;
    ~Table()=default;

    void set_name(string name_in){ name=name_in; }
    string get_name(){ return name; }

    void empty_table();

    int find_col_by_name(string in);

    bool check_key(const string &key, const bool &existence);

    static bool check_type(const string & type);

    void cast_data_to_col(const int &col_i, const string &type, const string &data);

    void auto_increment_col();

    bool set_INSERT_INTO_data(const vector<string> &elements_Names, const vector<string> &elementsValues);

    bool checkINSERT_INTOData_and_Nullify(const vector<string> &filled_elements);

    int get_col_index(const string &in);

    bool find_Rows_by_value(const string &data, const int &col_i, vector<int> &foundRows);

    void deleteRows(const vector<int> &rows);

    void empty_content();

    bool get_rows_by_data(const int &col_i, const string &searchData, vector<int> &foundRows);

    bool set_UPDATE_data(const vector<string> &data, const vector<int> &rows);

    void printCols(const vector <string> & colSelection);

    bool printTable_to_file(ofstream & out);

    void createTable_from_file(ifstream &in, string line);

    void createCol_from_file(ifstream &in, const string &type, int col_i);
};
#endif //CS_PROJECT_TABLE_H
