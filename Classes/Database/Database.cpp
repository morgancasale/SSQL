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

bool check_CREATE_syntax(string in, const bool &show_err){
    bool err=false;

    string first_line=substr_from_c_to_c(in, 0, 4, false);
    if(num_of_words(first_line)!=3){
        err=true;
    }
    if(first_line[first_line.size()-1]!='(' and !err){ //this check if there is a '(' after the table name
        err=true;
    }

    string line;
    int end2=in.find(");");
    if(end2!=-1 and !err){//this checks if there is the final substring ");" somewhere
        for(int i=0; i<end2 and !err and substr_from_c_to_c(in, 1, 1, '(', ')', false)!=" "; i++){ //this checks if every input starts with a space end ends with a ',', it considers input of two and three letters
            line=substr_from_c_to_c(in, 4, 1, ' ', ',', false);
            if(num_of_words(line)>4){
                err=true;
            }
            if(line=="/err" and !err){
                line=substr_from_c_to_c(in, 4, 1, ' ', ')', false);
                string line2=substr_from_c_to_c(in, 4, 2, ' ', ')', false);
                if(line=="/err" or line2=="/err"){
                    err=true;
                }
                erase_substr(in, line2);
                erase_substr(in, line);
            } else{
                erase_substr(in, line+", ");
            }
        }
    } else{
        err=true;
    }

    if(in.find(");")==-1 and !err){
        err=true;
    }

    if(err and show_err){
        cerr<<endl<<"CREATE command Syntax error!";
    }

    return err;
}
