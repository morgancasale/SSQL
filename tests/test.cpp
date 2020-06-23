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
    d4.START();
    string choice,command;

    Column<string> & Europian_Countries=(*static_cast<Column<string>*>(d4.Tables[0].cols[0]));
    Column<string> & American_Countries=(*static_cast<Column<string>*>(d4.Tables[1].cols[0]));

    Column<int> & Countries_ID=(*static_cast<Column<int>*>(d4.Tables[2].cols[0]));
    Column<string> & Countries_EU=(*static_cast<Column<string>*>(d4.Tables[2].cols[1]));
    Column<string> & Countries_AM=(*static_cast<Column<string>*>(d4.Tables[2].cols[2]));

    Column<string> & phone_name=(*static_cast<Column<string>*>(d4.Tables[3].cols[0]));
    Column<int> & Yor=(*static_cast<Column<int>*>(d4.Tables[3].cols[1]));
    Column<float> & price=(*static_cast<Column<float>*>(d4.Tables[3].cols[2]));
    Column<int> & Sef=(*static_cast<Column<int>*>(d4.Tables[3].cols[3]));

    Column<string> & model=(*static_cast<Column<string>*>(d4.Tables[4].cols[0]));
    Column<string> & company=(*static_cast<Column<string>*>(d4.Tables[4].cols[1]));
    Column<int> & yor=(*static_cast<Column<int>*>(d4.Tables[4].cols[2]));
    Column<float> & carPrice=(*static_cast<Column<float>*>(d4.Tables[4].cols[3]));
    Column<float> & speed=(*static_cast<Column<float>*>(d4.Tables[4].cols[4]));


    choice="Create table EUROPE ( EUROPIAN_COUNTRIES text, PRIMARY KEY (EUROPIAN_COUNTRIES));";
    bool noErr=d4.process_command(choice);

    //Column<string> & Europian_Countries=(*static_cast<Column<string>*>(d4.Tables[0].cols[0]));

    choice="insert into EUROPE (EUROPIAN_COUNTRIES) values (\"Italy\");";
    noErr=d4.process_command(choice);
    choice="insert into EUROPE (EUROPIAN_COUNTRIES) values (\"France\");";
    noErr=d4.process_command(choice);
    choice="insert into EUROPE (EUROPIAN_COUNTRIES) values (\"Greece\");";
    noErr=d4.process_command(choice);

    choice="Create table AMERICA ( AMERICAN_COUNTRIES text, PRIMARY KEY (AMERICAN_COUNTRIES));";
    noErr=d4.process_command(choice);

    //Column<string> & American_Countries=(*static_cast<Column<string>*>(d4.Tables[1].cols[0]));

    choice="insert into AMERICA (AMERICAN_COUNTRIES) values (\"USA\");";
    noErr=d4.process_command(choice);
    choice="insert into AMERICA (AMERICAN_COUNTRIES) values (\"Canada\");";
    noErr=d4.process_command(choice);
    choice="insert into AMERICA (AMERICAN_COUNTRIES) values (\"Mexico\");";
    noErr=d4.process_command(choice);

    choice="CREATE TABLE COUNTRIES ("
           " ID INT               NOT NULL,"
           " NAME_EUROPE TEXT,"
           " NAME_AMERICAN TEXT,"
           " PRIMARY KEY (ID),"
           " FOREIGN KEY (NAME_EUROPE) REFERENCES EUROPE (EUROPIAN_COUNTRIES),"
           " FOREIGN KEY (NAME_AMERICAN) REFERENCES AMERICA (AMERICAN_COUNTRIES)"
           ");";
    noErr=d4.process_command(choice);

    /*Column<int> & Countries_ID=(*static_cast<Column<int>*>(d4.Tables[2].cols[0]));
    Column<string> & Countries_EU=(*static_cast<Column<string>*>(d4.Tables[2].cols[1]));
    Column<string> & Countries_AM=(*static_cast<Column<string>*>(d4.Tables[2].cols[2]));*/

    choice=R"(insert Into COUNTRIES (ID, NAME_EUROPE, NAME_AMERICAN) VALUES ( 23, "Italy", "Mexico");)";
    noErr=d4.process_command(choice);

    choice="Update COUNTRIES "
           "seT NAME_EUROPE=\"Greece\", "
           "NAME_AMERICAN=\"USA\" "
           "WheRe ID= 23;";
    noErr=d4.process_command(choice);

    choice="CREATE table pHone ( Name tExt not null, yOr int not null, price float, sef int auto_increment not null, primary key(name) );";
    noErr=d4.process_command(choice);

    choice="insert into phone (yor, name, sef, price) values (2020, \"oneplus 8 pro\", 6, 1019.01);";
    if(d4.process_command(choice)){
        cout<<endl<<"INSERT command correctly processed!";
    }else{
        cerr<<":(";
    }

    choice="insert into phone (yor, name, sef, price) values (2016, \"samsung s7\", 6, 729.99);";
    noErr=d4.process_command(choice);
    choice="insert into phone (yor, name, sef, price) values (2013, \"iphone 5\", 5, 729.99);";
    noErr=d4.process_command(choice);

    /*Column<string> & phone_name=(*static_cast<Column<string>*>(d4.Tables[3].cols[0]));
    Column<int> & Yor=(*static_cast<Column<int>*>(d4.Tables[3].cols[1]));
    Column<float> & price=(*static_cast<Column<float>*>(d4.Tables[3].cols[2]));
    Column<int> & Sef=(*static_cast<Column<int>*>(d4.Tables[3].cols[3]));*/


    /*choice="update phone set  name=\"mmama\", yor=2017 where price = 729.99;";
    command=take_command(choice);
    if(d4.process_command(choice, command)){
        cout<<"Update command correctly processed!";
    } else{
        cout<<"Update :(";
    }*/


    choice="create table car ( model text not null, company text, yor int, price float, speed float, primary key(model) );";
    noErr=d4.process_command(choice);

    /*Column<string> & model=(*static_cast<Column<string>*>(d4.Tables[4].cols[0]));
    Column<string> & company=(*static_cast<Column<string>*>(d4.Tables[4].cols[1]));
    Column<int> & yor=(*static_cast<Column<int>*>(d4.Tables[4].cols[2]));
    Column<float> & price=(*static_cast<Column<float>*>(d4.Tables[4].cols[3]));
    Column<float> & speed=(*static_cast<Column<float>*>(d4.Tables[4].cols[4]));*/

    choice=R"(insert iNTo car ( model, company, yor, price, speed) values ( "Panda", "Fiat", 2012, 3000.0, 120.5);)";
    noErr=d4.process_command(choice);

    choice=R"(insert iNTo car ( model, yor, price) values ( "C3 Picasso", 2006, 5000.5);)";
    noErr=d4.process_command(choice);

    choice=R"(insert iNTo car ( model, company, yor, price, speed) values ( "Grand Cherokee", "Jeep", 2012, 68000.0, 140.0);)";
    noErr=d4.process_command(choice);

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
    noErr=d4.process_command(choice);

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
    cout<<b;*/