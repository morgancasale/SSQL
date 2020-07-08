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
                  "numberionero int not null, "
                  "name text not null, "
                  "price float not null, "
                  "cariocano char, "
                  "primary key(numberionero) );";
    d4.process_command(choice, quit);

    choice="insert into phone (numberionero, name, price, cariocano) values (-1000000, \"carlo pietro tabasso\", -4252526.01, 'p');";
    d4.process_command(choice, quit);
    choice="insert into phone (numberionero, name, price, cariocano) values (2098, \"morgan stefano maria casale\", -0.0000005684, 'p');";
    d4.process_command(choice, quit);
    choice="insert into phone (numberionero, name, price, cariocano) values (2079, \"nicolo' ribaudo\", -9.72485, 'p');";
    d4.process_command(choice, quit);

    choice="SELECT cariocano, numberionero, price, name FROM phone WHERE cariocano = 'p';";
    choice="SELECT number, name, price, car FROM phone WHERE car between 'c' and 'r' order by number asc;";
    d4.process_command(choice, quit);

    return 0;
}
