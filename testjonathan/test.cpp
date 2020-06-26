#include <iostream>
#include <fstream>

using namespace std;
#include "../Classes/Time/Time.cpp"
#include "../Classes/Date/Date.cpp"
#include "../utility.h"
#include "../syntax.h"
#include "../Classes/Table/Table.cpp"
#include "../Classes/Database/Database.cpp"

int main(){
    Database d4;
    //d4.START();
    string choice,command;

    choice="Create table EUROPE ( EUROPIAN_COUNTRIES text, PRIMARY KEY (EUROPIAN_COUNTRIES));";
    d4.process_command(choice, <#initializer#>);

    choice="Create table AMERICA ( AMERICAN_COUNTRIES text, PRIMARY KEY (AMERICAN_COUNTRIES));";
    d4.process_command(choice, <#initializer#>);

    choice="CREATE TABLE COUNTRIES ("
           " ID INT               NOT NULL,"
           " NAME_EUROPE TEXT,"
           " NAME_AMERICAN TEXT,"
           " PRIMARY KEY (ID),"
           " FOREIGN KEY (NAME_EUROPE) REFERENCES EUROPE (EUROPIAN_COUNTRIES),"
           " FOREIGN KEY (NAME_AMERICAN) REFERENCES AMERICA (AMERICAN_COUNTRIES)"
           ");";
    d4.process_command(choice, <#initializer#>);

    choice="CREATE table pHone ( Name tExt not null, yOr int not null, price float, sef int auto_increment not null, primary key(name) );";
    d4.process_command(choice, <#initializer#>);

    choice="insert into phone (yor, name, sef, price) values (2020, \"oneplus 8 pro\", 6, 1019.01);";
    if(d4.process_command(choice, <#initializer#>)){
        cout<<endl<<"INSERT command correctly processed!";
    }else{
        cerr<<":(";
    }

    choice="insert into phone (yor, name, sef, price) values (2016, \"samsung s7\", 6, 729.99);";
    d4.process_command(choice, <#initializer#>);
    choice="insert into phone (yor, name, sef, price) values (2013, \"iphone 5\", 5, 729.99);";
    d4.process_command(choice, <#initializer#>);

    Column<string> & a=(*static_cast<Column<string>*>(d4.Tables[0].cols[0]));
    Column<int> & b=(*static_cast<Column<int>*>(d4.Tables[0].cols[1]));
    Column<float> & c=(*static_cast<Column<float>*>(d4.Tables[0].cols[2]));
    Column<int> & d=(*static_cast<Column<int>*>(d4.Tables[0].cols[3]));


    /*choice="update phone set  name=\"mmama\", yor=2017 where price = 729.99;";
    command=take_command(choice);
    if(d4.process_command(choice, command)){
        cout<<"Update command correctly processed!";
    } else{
        cout<<"Update :(";
    }*/


    choice="create table car ( model text not null, company text, yor int, price float, speed float, primary key(model) );";
    d4.process_command(choice, <#initializer#>);

    Column<string> h=(*static_cast<Column<string>*>(d4.Tables[0].cols[0]));
    Column<string> r=(*static_cast<Column<string>*>(d4.Tables[1].cols[0]));

    /*choice="delete phone where sef=6;";
    command=take_command(choice);
    if(d4.process_command(choice, command)){
        cout<<endl<<"DELETE command correctly processed!";
    }else{
        cerr<<":(";
    }

    choice="truncate table phone;";
    command=take_command(choice);
    d4.process_command(choice, command);





    choice="drop table car;";
    command=take_command(choice);
    d4.process_command(choice, command);*/

    choice="quit();";
    d4.process_command(choice, <#initializer#>);

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
    cout<<substrcc(b, 2, 3, ' ', ' ',false);

    bool c;
    if(c=check_CREATE_syntax(b)){
        cout<<"1st test -> success";
    }
    vector<string> data=get_CREATE_data(b);
*/