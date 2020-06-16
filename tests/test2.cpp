#include <iostream>
#include "../Classes/Time/Time.cpp"
#include "../Classes/Date/Date.cpp"
#include "../utility.h"
#include "../syntax.h"
#include "../Classes/Table/Table.cpp"
#include "../Classes/Database/Database.cpp"
using namespace std;


int main(){
    Database d4;
    string choice="CREATE table phone ( number int not null, name text not null, primary key(number) );";
    string command=take_command(choice);
    d4.process_command(choice, command);

    choice="insert into phone (number, name) values (2020, \"carlo\");";
    command=take_command(choice);
    d4.process_command(choice, command);

    choice="SELECT number, name FROM phone;";
    command=take_command(choice);
    d4.process_command(choice, command);


    return 0;
}