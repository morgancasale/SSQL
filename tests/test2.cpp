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
    string choice="CREATE table phone ( "
                  "number int not null, "
                  "name text not null, "
                  "price float not null, "
                  "car char, "
                  "primary key(number) );";
    string command=take_command(choice);
    d4.process_command(choice, command);

    choice="insert into phone (number, name, price) values (2020, \"carlo\", 12.89);";
    command=take_command(choice);
    d4.process_command(choice, command);
    choice="insert into phone (number, name, price, car) values (2098, \"morgan\", 0.5, 'p');";
    command=take_command(choice);
    d4.process_command(choice, command);
    choice="insert into phone (number, name, price, car) values (2079, \"nicolo'\", 9.72, 'p');";
    command=take_command(choice);
    d4.process_command(choice, command);

    choice="SELECT number, name, price, car FROM phone WHERE car = 'p';";
    command=take_command(choice);
    d4.process_command(choice, command);


    return 0;
}