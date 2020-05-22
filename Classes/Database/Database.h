#ifndef CS_PROJECT_DATABASE_H
#define CS_PROJECT_DATABASE_H
#include <vector>
#include "../Table/Table.h"

class Database {
public:
    vector<Table> Tables;
    vector<string> TablesNames;

    string allowed_coms[8]={
            "create table",
            "drop table",
            "trunc table",
            "insert into",
            "delete from",
            "update",
            "select",
            "quit()"
    };

    bool process_command(const string &choice, const string &command);
    bool check_command(const string &input, const bool &show_error, string &command= (string &) "temp");

    bool check_Table(const string &in, bool show_err=false);

    bool INSERT_INTO(string in);

    bool delete_Table(string command);

    bool empty_Table(string command);

    bool add_Row_to_Table(string command);

    bool delete_Row_from_Table(string command);

    bool update_Row_data(string command);

    bool print_selected_data(string command);

    int find_Table(const string & in);

    ~Database()=default;

    void get_INSERT_INTO_data(string in, const int & Table_i, vector<string> &elementsNames,
                              vector<string> &elementsValues);

    bool set_INSERT_INTO_data(string in, const int &Table_i, const vector<string> &elementsNames,
                              const vector<string> &elementsValues);
};

void a(const string &in){
    cout<<in;
}
//bool check_CREATE_syntax(string in, const bool &show_err=true); //solve privacy problem

#endif //CS_PROJECT_DATABASE_H
