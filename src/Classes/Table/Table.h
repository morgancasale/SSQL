#ifndef CS_PROJECT_TABLE_H
#define CS_PROJECT_TABLE_H
#include "../../syntax.h"
#include <fstream>
using namespace std;

template<typename type> class Column {
    public:
        vector<type> values;
        vector<bool> valuesNullity;
        string key;
        bool not_null=false;
        bool auto_increment=false;
        Column()=default;
        ~Column()=default;
};

class Table {
    private:
        int primaryKey_index=0;
        int rows=0;
        bool Foreign_linked=false;
        vector<void *> cols;
        vector<string> elementsNames;
        vector<string> elementsTypes;
        vector<int> ForeignTables, ForeignCols, ConnectedCols;


public:
        string name;
        Table()=default;
        ~Table()=default;

//Getters and Setters:

    const vector<void *> & get_cols() const{ return cols; }

    const vector<int> & get_ForeignCols() const { return ForeignCols; }
    void set_ForeignCols(const vector<int> & foreignCols) { ForeignCols = foreignCols; }

    const vector<int> & get_ConnectedCols() const { return ConnectedCols; }
    void set_ConnectedCols(const vector<int> & connectedCols) { ConnectedCols = connectedCols; }

    vector<string> get_elementsTypes() const { return elementsTypes; }
    void set_elementsTypes(const vector<string> & in){ elementsTypes=in; }

    const int & get_rows() const{ return rows; }
    void set_rows(const int & num){ rows=num; }

    const vector<int> & get_ForeignTables() const { return ForeignTables; }
    void set_ForeignTables(const vector<int> & in){ ForeignTables=in; }

    bool get_Foreign_linked() const { return Foreign_linked; }
    void set_Foreign_linked(bool foreignLinked) { Foreign_linked = foreignLinked; }

//Methods:
    private:
        static vector<string> get_CREATE_data(string in);
        static int count_data(const vector<string> &data, const string &type);

        bool set_primaryKey(const string & in);
        bool create_col(string in, bool existence);
        bool check_key(const string &key, bool existence=false);
        static bool check_type(const string & type);
        void cast_data_to_col(const int &col_i, const string &type, const string &data);
        void col_orderer(int colIndex, vector <int> & rowsIndexes, int order);
        void createCol_from_file(ifstream &in, const string &type, const int &col_i);

    public:
        void delete_col(const unsigned int &i);

        bool set_Table(const string &in);

        void auto_increment_col();

        bool set_INSERT_INTO_data(const vector<string> &elements_Names, const vector<string> &elementsValues);

        bool checkINSERT_INTOData_and_Nullify(vector<string> filled_elements);

        int get_col_index(const string &in);

        bool find_Rows_by_value(string data1, const int &col_i, vector<int> &foundRows, const string & op, string data2);

        void deleteRows(const vector<int> &Rows);

        void empty_Tablecontent();

        bool set_UPDATE_data(const vector<string> &data, const vector<int> &rows);

        bool printCols(vector <string> colSelection,
                       const vector <string> & search = {"/err", "0", "/err"},
                       const string &colToOrder="/err", const int &order=0 );

        void printTable_to_file(ofstream &out);

        void createTable_from_file(ifstream &in, string line);
};

#endif //CS_PROJECT_TABLE_H