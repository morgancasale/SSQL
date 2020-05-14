#include "utility.h"
#include "Classes/Table/Table.h"
#include "Classes/Database/Database.h"

Database data1;

string allowed_coms[8]={
        "create table",
        "drop table",
        "trunc table",
        "insert into",
        "delete from",
        "update",
        "select",
        "quit()"
};


bool process_command(const string &choice, const string &command) {
    if(command=="quit()"){
    } else
    if(command=="create table"){
        Table temp(choice); //this creates a temporary Table
        data1.Tables.resize(data1.Tables.size()+1);
        data1.Tables[data1.Tables.size()]=temp; //that is copied to the last ( == new ) Table of the Database
    } else
    if(command=="drop table"){
        delete_Table(choice);
    } else
    if(command=="trunc table"){
        empty_Table(choice);
    } else
    if(command=="insert into") {
        add_Row_to_Table(choice);
    } else
    if(command=="delete from"){
        delete_Row_from_Table(choice);
    } else
    if(command=="update"){
        update_Row_data(choice);
    } else
    if(command=="select"){
        print_selected_data(choice);
    }
}

bool check_command(const string &input, const bool &show_error, string &command= (string &) "temp") {
    bool err=true;
    for(const string &tmp :allowed_coms){ //this loop checks if in the input string there's an allowed command, and if found writes it in the variable "command"
        if(((command= substr_from_c_to_c(input, 0, 1, ' ')) == tmp) or ((command= substr_from_c_to_c(input, 0, 2, ' ')) == tmp)){
            err=false;
        }
    }
    if(show_error and !err){
        cerr<<"This command doesn't exist!";
    }
    return err;
}
