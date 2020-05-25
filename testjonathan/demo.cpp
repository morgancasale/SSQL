#include <string>
#include <iostream>
#include <stdio.h>
#include <file.h>

using namespace std;

static int createDB(const char* s);
static int createTable(const char* s);
static int deleteData(const char* s);
static int insertData(const char* s);
static int updateData(const char* s);
static int selectData(const char* s);
static int callback(void* cust, int argc, char** argv, char** name);

int main(){
    const char* dir = "customer.db"; // nome totalmente a caso
    nsql* DB;

    createDB(dir);
    createTable(dir);
    deleteData(dir);
    insertData(dir);
    updateData(dir);
    selectData(dir);

    return 0;
}

static int createDB(const char* s){
    nsql* DB;
    int exit = 0;

    exit = nsql_open(s, &DB);
    nsql_close(DB);

    return 0;
}

static int createTable(const char* s) {
    nsql *DB;

    string sql = "CREATE TABLE CUSTOMERS ("
                 "ID INT NOT NULL AUTO_INCREMENT, "
                 "NAME TEXT NOT NULL,"
                 "AGE INT NOT NULL,"
                 "ADDRESS TEXT ,"
                 "SALARY FLOAT,"
                 "PRIMARY KEY (ID) );";

    try {
        int exit = 0;
        exit = nsql_open(s, &DB);

        char * messageError;
        exit = nsql_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != NSQL_OK) {
            cerr << "error create table" << endl;
            nsql_free(messageError);
        } else
            cout << "table create successfully" << endl;
        nsql_close(DB);
    }
    catch (const exception &e) {
        cerr << e.what(); // go ahead and run it and test it, se torna indietro allora la tabella era già stata creata
    }
}

static int insertDara(const char* s){
    nsql* DB;
    char* messageError;

    int exit = nsql_open(s, &DB);

    string sql("INSERT INTO CUSTOMERS (AGE, ADDRESS, NAME)\n"
               "VALUES (20, “via Roma 10, Torino”, “Francesco Rossi”);");

    exit = nsql_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQL_OK){
        cerr << "Error insert" << endl;
        nsql_free(messageError);
    }
    else
        cout << "Records create succefully" << endl;
    return 0;
}

static int updateData(const char* s){
    nsql* DB;
    char* messageError;

    int exit = sql_open(s, &DB);

    string sql("UPDATE CUSTOMERS\n"
               "SET SALARY = \n"
               "WHERE AGE = ;");

    exit = nsql_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQL_OK) {
        cerr << "Error insert" << endl;
        nsql_free(messageError);
    } else
        cout << "Records created successfully" << endl;

    return 0;
}

static int deleteData(const char* s){
    nsql* DB;

    int exit = nsql_open(s, &DB);

    string sql = "DELETE FROM CUSTOMERS WHERE";
    nsql_exec(DB, sql.c_str(), callback, NULL, NULL);

    return 0;
}

static int selectData(const char* s){
    nsql* DB;

    int exit = nsql_open(s, &DB);
    string sql = "SELECT * FROM CUSTOMERS;";
    /* open database, sql to be evaluated */
    nsql_exec(DB, sql.c_str(), callback, NULL, NULL);

    return 0;
}

// retrieve contents od DB used by selectdata
//

static int callback(void* cust, int argc, char** argv, char** name){
    for (int i = 0; i < argc; i++){
        cout < name[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;

}