#ifndef CS_PROJECT_DATABASE_H
#define CS_PROJECT_DATABASE_H
#include "../Table/Table.h"

class Database {
private:
    vector<Table> Tables;
    vector<string> deleted_TablesNames;
    vector<string> updated_TablesNames;

//Public methods:
public:
    bool START();

    bool process_command(string choice, bool &quit);

    bool readCommands_from_file(const string &filepath, bool &quit);

    Database() = default;
    ~Database()=default;

private:

//Main methods
    bool CREATE_TABLE(string in);
    bool INSERT_INTO(string in);
    bool DELETE(const string& in);
    bool DROP_TABLE(const string &in);
    bool TRUNCATE_TABLE(const string &in);
    bool UPDATE(string in);
    bool SELECT(string in);
    void QUIT();

//Other Methods
    bool check_Table_existence(const string &in_Table_name, const bool & check_existence);

    int find_Table(const string& in);

    static bool get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues);

    static bool check_TableName(const string &name);

    bool setForeignKeys(string data, Table &thisTable);

    bool checkForeignKeys(const Table &table, int row=-1);
};

#endif //CS_PROJECT_DATABASE_H