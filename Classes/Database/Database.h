#ifndef CS_PROJECT_DATABASE_H
#define CS_PROJECT_DATABASE_H
#include <vector>
#include "../Table/Table.h"

class Database {
public:
    vector<Table> Tables;
};

bool delete_Table(string command);

bool empty_Table(string command);

bool add_Row_to_Table(string command);

bool delete_Row_from_Table(string command);

bool update_Row_data(string command);

bool print_selected_data(string command);

#endif //CS_PROJECT_DATABASE_H
