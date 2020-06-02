#include <iostream>
#include "Classes/Table/Table.cpp"
#include "syntax.h"
#include "utility.h"
#include "Classes/Date/Date.cpp"
#include "Classes/Time/Time.cpp"
#include "core.h"
using namespace std;

int main(int argc, char **argv) {
    Database data1;

    //first recover database data from file

    if(argc>2){
        //script=true;
        //data1.process_script_command(argv[1]);
    }
    string choice;
    string command;
    int comm_i=0;
    do{
        if(argc==1){
            //script=true;
            choice=get_command_from_file(argv[1], comm_i);
        }
        if(argc==2){
            cout<<"Waiting for command: ";
            cin>>choice;
        }

        command=take_command(choice);
        if(command!="/err") data1.process_command(choice, command);

    }while(command!="quit()");



    return 0;
}

