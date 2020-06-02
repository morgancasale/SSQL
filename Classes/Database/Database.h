#ifndef CS_PROJECT_DATABASE_H
#define CS_PROJECT_DATABASE_H
#include <vector>
#include "../Table/Table.h"
class Database {
public:
    vector<Table> Tables;
    vector<string> TablesNames;
    bool process_command(const string &choice, const string &command);
    static bool check_command(const string &input, const bool &show_error, string &command= (string &) "temp");

    bool check_Table_existence(const string &in, const bool & existence);

    bool INSERT_INTO(string in);
    bool DELETE(string in);

    bool delete_Table(string command);

    bool empty_Table(string command);

    bool add_Row_to_Table(string command);

    bool delete_Row_from_Table(string command);

    bool update_Row_data(string command);

    bool print_selected_data(string command);

    int find_Table(const string & in);

    Database() = default;

    ~Database()=default;

    static void get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues);

    bool set_INSERT_INTO_data(const int &Table_i, const vector<string> &elementsNames,
                              const vector<string> &elementsValues);

    bool check_INSERT_INTO_data(const int &Table_i, const vector<string> & filled_elements);

    void auto_increment(const int &Table_i);

    bool cast_data(Table &table, const int & Table_i, const int &col_i, const string &type, const string &data);

    static bool check_TableName(const string &name);
};

void a(const string &in){
    cout<<in;
}
//bool check_CREATE_syntax(string in, const bool &show_err=true); //solve privacy problem

#endif //CS_PROJECT_DATABASE_H
