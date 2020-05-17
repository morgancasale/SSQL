#ifndef CS_PROJECT_DATABASE_H
#define CS_PROJECT_DATABASE_H
#include <vector>
#include "../Table/Table.h"

class Database {
public:
    vector<Table> Tables;

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

    bool check_Table(const string &in, const bool show_err=false);


    bool delete_Table(string command);

    bool empty_Table(string command);

    bool add_Row_to_Table(string command);

    bool delete_Row_from_Table(string command);

    bool update_Row_data(string command);

    bool print_selected_data(string command);

    ~Database()=default;
};

bool check_CREATE_syntax(string in, const bool &show_err=true); //solve privacy problem

#endif //CS_PROJECT_DATABASE_H
