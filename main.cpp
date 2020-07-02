#include <iostream>
#include "Classes/Time/Time.cpp"
#include "Classes/Date/Date.cpp"
#include "syntax.h"
#include "Classes/Table/Table.cpp"
#include "Classes/Database/Database.cpp"
using namespace std;

int main(int argc, char **argv) {
    bool noErr=true, QUIT=false;
    Database d4;
    //d4.START();

    //if(argc>2){
        noErr= d4.readCommands_from_file("../script.sql", QUIT); // (argv[1]);
    //}

    string choice;
    string command;
    do{
        cout<<endl<<endl<<"Waiting for command: "<<endl;
        cin>>choice;

        command=take_command(choice);
        d4.process_command(choice, QUIT);

    }while(!QUIT);

    return 0;
}

