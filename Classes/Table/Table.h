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
    vector<string> elementsTypes;
    vector<string> elementsNames;
    vector<void *> cols;
    static bool check_CREATE_syntax(string in, const bool &show_err=true);
    static vector<string> get_CREATE_data(string in);
public:
    void* create_col(string in);

public:
    explicit Table(const string &in);
    Table()=default;
    void Table2(const string &in);
    ~Table()=default;
    string get_name(){return name;}
};
#endif //CS_PROJECT_TABLE_H
