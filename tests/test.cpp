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
    bool QUIT=false;
    d4.readCommands_from_file("../script.sql", QUIT);
    //d4.START();
    string command;

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

    Column<string> & nomeMoto=(*static_cast<Column<string>*>(d4.Tables[5].cols[0]));
    Column<string> & companyMoto=(*static_cast<Column<string>*>(d4.Tables[5].cols[1]));
    Column<string> & colorMoto=(*static_cast<Column<string>*>(d4.Tables[5].cols[2]));
    Column<int> & wheelsMoto=(*static_cast<Column<int>*>(d4.Tables[5].cols[3]));

    Column<string> & motoModel=(*static_cast<Column<string>*>(d4.Tables[5].cols[0]));

    command="Create table EUROPE ( EUROPIAN_COUNTRIES text, PRIMARY KEY (EUROPIAN_COUNTRIES));";
    bool noErr= d4.process_command(command, QUIT);

    //Column<string> & Europian_Countries=(*static_cast<Column<string>*>(d4.Tables[0].cols[0]));

    command="insert into EUROPE (EUROPIAN_COUNTRIES) values (\"Italy\");";
    noErr= d4.process_command(command, QUIT);
    command="insert into EUROPE (EUROPIAN_COUNTRIES) values (\"France\");";
    noErr= d4.process_command(command, QUIT);
    command="insert into EUROPE (EUROPIAN_COUNTRIES) values (\"Greece\");";
    noErr= d4.process_command(command, QUIT);

    command="Create table AMERICA ( AMERICAN_COUNTRIES text, PRIMARY KEY (AMERICAN_COUNTRIES));";
    noErr= d4.process_command(command, QUIT);

    //Column<string> & American_Countries=(*static_cast<Column<string>*>(d4.Tables[1].cols[0]));

    command="insert into AMERICA (AMERICAN_COUNTRIES) values (\"USA\");";
    noErr= d4.process_command(command, QUIT);
    command="insert into AMERICA (AMERICAN_COUNTRIES) values (\"Canada\");";
    noErr= d4.process_command(command, QUIT);
    command="insert into AMERICA (AMERICAN_COUNTRIES) values (\"Mexico\");";
    noErr= d4.process_command(command, QUIT);

    command="CREATE TABLE COUNTRIES ("
           " ID INT               NOT NULL,"
           " NAME_EUROPE TEXT,"
           " NAME_AMERICAN TEXT,"
           " PRIMARY KEY (ID),"
           " FOREIGN KEY (NAME_EUROPE) REFERENCES EUROPE (EUROPIAN_COUNTRIES),"
           " FOREIGN KEY (NAME_AMERICAN) REFERENCES AMERICA (AMERICAN_COUNTRIES)"
           ");";
    noErr= d4.process_command(command, QUIT);


    /*Column<int> & Countries_ID=(*static_cast<Column<int>*>(d4.Tables[2].cols[0]));
    Column<string> & Countries_EU=(*static_cast<Column<string>*>(d4.Tables[2].cols[1]));
    Column<string> & Countries_AM=(*static_cast<Column<string>*>(d4.Tables[2].cols[2]));*/

    command=R"(insert Into COUNTRIES (ID, NAME_EUROPE, NAME_AMERICAN) VALUES ( 23, "Italy", "Mexico");)";
    noErr= d4.process_command(command, QUIT);

    command="Update COUNTRIES "
           "seT NAME_EUROPE=\"Greece\", "
           "NAME_AMERICAN=\"USA\" "
           "WheRe ID= 23;";
    noErr= d4.process_command(command, QUIT);

    command="CREATE table pHone ( Name tExt not null, yOr int not null, price float, sef int auto_increment not null, primary key(name) );";
    noErr= d4.process_command(command, QUIT);

    command="insert into phone (yor, name, sef, price) values (2020, \"oneplus 8 pro\", 6, 1019.01);";
    if(d4.process_command(command, QUIT)){
        cout<<endl<<"INSERT command correctly processed!";
    }else{
        cerr<<":(";
    }

    command="insert into phone (yor, name, sef, price) values (2016, \"samsung s7\", 6, 729.99);";
    noErr= d4.process_command(command, QUIT);
    command="insert into phone (yor, name, sef, price) values (2013, \"iphone 5\", 5, 729.99);";
    noErr= d4.process_command(command, QUIT);

    /*Column<string> & phone_name=(*static_cast<Column<string>*>(d4.Tables[3].cols[0]));
    Column<int> & Yor=(*static_cast<Column<int>*>(d4.Tables[3].cols[1]));
    Column<float> & price=(*static_cast<Column<float>*>(d4.Tables[3].cols[2]));
    Column<int> & Sef=(*static_cast<Column<int>*>(d4.Tables[3].cols[3]));*/


    /*command="update phone set  name=\"mmama\", yor=2017 where price = 729.99;";
    if(d4.process_command(command)){
        cout<<"Update command correctly processed!";
    } else{
        cout<<"Update :(";
    }*/


    command="create table car ( model text not null, company text, yor int, price float, speed float, primary key(model) );";
    noErr= d4.process_command(command, QUIT);

    /*Column<string> & model=(*static_cast<Column<string>*>(d4.Tables[4].cols[0]));
    Column<string> & company=(*static_cast<Column<string>*>(d4.Tables[4].cols[1]));
    Column<int> & yor=(*static_cast<Column<int>*>(d4.Tables[4].cols[2]));
    Column<float> & price=(*static_cast<Column<float>*>(d4.Tables[4].cols[3]));
    Column<float> & speed=(*static_cast<Column<float>*>(d4.Tables[4].cols[4]));*/

    command=R"(insert iNTo car ( model, company, yor, price, speed) values ( "Panda", "Fiat", 2012, 3000.0, 120.5);)";
    noErr= d4.process_command(command, QUIT);

    command=R"(insert iNTo car ( model, yor, price) values ( "C3 Picasso", 2006, 5000.5);)";
    noErr= d4.process_command(command, QUIT);

    command=R"(insert iNTo car ( model, company, yor, price, speed) values ( "Grand Cherokee", "Jeep", 2012, 68000.0, 140.0);)";
    noErr= d4.process_command(command, QUIT);

    /*command="delete phone where sef=6;";
    if(d4.process_command(command)){
        cout<<endl<<"DELETE command correctly processed!";
    }else{
        cerr<<":(";
    }

    command="truncate table phone;";
    d4.process_command(command);

    command="drop table car;";
    d4.process_command(command);*/

    command="quit();";
    noErr= d4.process_command(command, QUIT);

    return 0;
}