#include <iostream>
using namespace std;
#include "../Classes/Time/Time.cpp"
#include "../Classes/Date/Date.cpp"
#include "../utility.h"
#include "../syntax.h"
#include "../Classes/Table/Table.cpp"
#include "../Classes/Database/Database.cpp"

int main(){
    Database d4;
    string choice="create table phone ( name text not null, yor int not null, price float, sef int auto_increment not null, primary key(name) );";
    string command=take_command(choice);
    if(d4.process_command(choice, command)){
        cout<<endl<<"CREATE command correctly processed!";
    }else{
        cerr<<":(";
    }

    choice="insert into phone (yor, name, sef, price) values (2020, \"oneplus 8 pro\", 6, 1019.01);";
    command=take_command(choice);
    if(d4.process_command(choice, command)){
        cout<<endl<<"INSERT command correctly processed!";
    }else{
        cerr<<":(";
    }
    Column<string> b=(*static_cast<Column<string>*>(d4.Tables[0].cols[0]));
    Column<int> a=(*static_cast<Column<int>*>(d4.Tables[0].cols[1]));
    Column<float> c=(*static_cast<Column<float>*>(d4.Tables[0].cols[2]));
    Column<int> d=(*static_cast<Column<int>*>(d4.Tables[0].cols[3]));
    cout<<"a";
    return 0;
}

/*
    stringstream ss=data_ss("ciao,dsfhgj", ',');

    Time time;
    cout<<time.get_hours();

    Date date;
    cout<<date.get_day();

    cout<<endl<<character_counter("ccccc", 'c');

    if(!control_create("frguhk")) cout<<endl<<"A";

    Table table;
    table.set_name("ciao");
    cout<<endl<<table.get_name();

    Database aaaa;
    cout<<endl<<aaaa.allowed_coms[0];

    cout<<"a";
*/

/*
    vector<void *> a;
    static vector<int> j;
    j.resize(2);
    col<string> g;
    g.set_value("mamma");
    int b=3;
    float c=3.45;
    vector<int> e={1,2,3,4};
    a.resize(3);
    a[0]=static_cast<void *>(&e);
    a[1]=static_cast<void *>(&c);
    a[2]= static_cast<void *>(&g);
    cout<< (*static_cast<vector<int>*>(a[0]))[2] << " " << *static_cast<float *>(a[1])<<" ";
    cout<< (*static_cast<col<string> *>(a[2])).get_value();
 */

/*string b="CREATE TABLE CUSTOMERS ( ID INT NOT NULL, NAME TEXT NOT NULL, AGE INT NOT NULL, ADDRESS TEXT , SALARY FLOAT, PRIMARY KEY (ID) );";
    clean_input(b);
    cout<<substr_from_c_to_c(b, 2, 3, ' ', ' ',false);

    bool c;
    if(c=check_CREATE_syntax(b)){
        cout<<"1st test -> success";
    }
    vector<string> data=get_CREATE_data(b);
    cout<<b;*/