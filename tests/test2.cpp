#include <iostream>
#include "../Classes/Time/Time.cpp"
#include "../Classes/Date/Date.cpp"
#include "../utility.h"
#include "../syntax.h"
#include "../Classes/Table/Table.cpp"
#include "../Classes/Database/Database.cpp"
using namespace std;
//NOTE PER CARLO DEL FUTURO:
//fchgvhbknjlmò
// sistemare between nelle varie funzioni e finire controllo sintassi di update
//xcfjgvbnmò
//cgvhnklmò

int main(){
    Database d4;
    bool quit=false;
    string choice="CREATE table phone ( "
                  "number int not null, "
                  "name text not null, "
                  "price float not null, "
                  "car char, "
                  "primary key(number) );";
    d4.process_command(choice, quit);

    choice="insert into phone (number, name, price) values (2020, \"carlo\", 12.89);";
    d4.process_command(choice, quit);
    choice="insert into phone (number, name, price, car) values (2098, \"morgan\", 0.5, 'p');";
    d4.process_command(choice, quit);
    choice="insert into phone (number, name, price, car) values (2079, \"nicolo'\", 9.72, 'h');";
    d4.process_command(choice, quit);

    choice="SELECT number, name, price, car FROM phone WHERE car between 'p' and 'c' order by number asc;";
    d4.process_command(choice, quit);

    return 0;
}
