#include "Database.h"
#include "../../core.h"

bool Database::check_Table(const string &in, const bool show_err) {
    bool err=false;
    string in_Table_name=substr_from_c_to_c(in,2,3);
    int i=0;
    do{
        if(Tables[i].get_name()==in_Table_name){
            err=true;
        }
        i++;
    }while((i<Tables.size()) and !err);

    if(err and show_err){
        cerr<<"Table named"<<in_Table_name<<" already exists!"<<endl;
        cerr<<"Choose another name.";
    }

    return err;
}

bool Database::process_command(const string &choice, const string &command) {
    if(command=="quit()"){
    } else
    if(command=="create table"){
        if(check_Table(choice, true)){
            Table temp(choice); //this creates a temporary Table
            Tables.resize(Tables.size()+1);
            Tables[Tables.size()]=temp; //that is copied to the last ( == new ) Table of the Database
        }
    } else
    if(command=="drop table"){
        bool err=true;  int j=0;
        for(int i=0; i<Tables.size(); i++){
            if(Tables[i].get_name() == choice)  err=false;   j=i;
        }
        if(!err) Tables.erase(Tables.begin()+j);
        else     cerr<<"la tabella non esiste"<<endl;
    } else
    if(command=="trunc table"){
        bool err=true;  int j=0;
        for(int i=0; i<Tables.size(); i++){
            if(Tables[i].get_name() == choice)  err=false;   j=i;
        }
        if(!err){
            Tables[j].empty_table();
        }
        else cerr<<"la tabella non esiste"<<endl;
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

bool Database::check_command(const string &input, const bool &show_error, string &command) { //checks whatever the command exists
    bool err=true;
    for(const string &tmp :allowed_coms){ //this loop checks if in the input string there's an allowed command, and if found writes it in the variable "command"
        if(((command= substr_from_c_to_c(input, 0, 1, ' ')) == tmp) or ((command= substr_from_c_to_c(input, 0, 2, ' ')) == tmp)){
            err=false;
        }
    }
    if(show_error and err){
        cerr<<"This command doesn't exist!";
    }
    return err;
}

