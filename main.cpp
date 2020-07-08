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

    if(argc>1){
        noErr= d4.readCommands_from_file(argv[1], QUIT);
    }

    if(noErr){
        cout<<"Input file "<<argv[1]<<" correctly read.";
    }

    string choice;
    do{
        cout<<endl<<endl<<"Waiting for next command: "<<endl;
        cin>>choice;

        d4.process_command(choice, QUIT);
    }while(!QUIT);

    return 0;
}