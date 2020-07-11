#ifndef CS_PROJECT_DATABASE_H
#define CS_PROJECT_DATABASE_H
#include "../Table/Table.h"

class Database {
public:
    vector<Table> Tables;

    Database() = default;
    ~Database()=default;

//Methods:
    bool process_command(string choice, bool &quit);

    bool START();

    bool readCommands_from_file(const string &filepath, bool &quit);

private:
    bool check_Table_existence(const string &in_Table_name, const bool & check_existence);

    bool INSERT_INTO(string in);
    bool DELETE(const string& in);

    bool PRINT(string in);

    int find_Table(const string& in);

    static bool get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues);

    static bool check_TableName(const string &name);

    bool DROP_TABLE(const string &in);

    bool TRUNCATE_TABLE(const string &in);

    bool UPDATE(string in);

    void QUIT();

    bool CREATE_TABLE(string in);

    bool setForeignKeys(string data, Table &thisTable);

    bool checkForeignKeys(const Table &table, int row=-1);


    //static bool check_command(const string &input, const bool &show_error, string &command= (string &) "temp");
};

#endif //CS_PROJECT_DATABASE_H