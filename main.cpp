#include <iostream>
#include "core.h"
using namespace std;

int main() {
    cout<<"Welcome to NSQL!"<<endl; //magari cambiare colore e aggiungere un po' di ascii art
    string choice;
    do{
        cout<<"Waiting for command: ";
        cin>>choice;
        tolower(choice);
        string command;
        if(check_command(choice, true, command)){
            process_command(choice, command);
        }
    }while(choice!="quit()");
    return 0;
}

