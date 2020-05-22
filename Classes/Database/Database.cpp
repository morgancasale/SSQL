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

bool Database::INSERT_INTO(string in){
    bool err=false;

    string Table=substr_from_c_to_c(in, 0, 1, ' ', ' ', false);
    erase_substr(in, Table+" (");
    int Table_i=find_Table(Table);

    if(Table_i!=-1) {
        vector<string> elementsNames;
        vector<string> elementsValues;
        get_INSERT_INTO_data(in, Table_i, elementsNames, elementsValues);
        set_INSERT_INTO_data(in, Table_i, elementsNames, elementsValues);
    } else{
        cerr<<endl<<"There is no Table with name "<<Table<<"!";
        return false;
    }

}

void Database::get_INSERT_INTO_data(string in, const int & Table_i, vector<string> & elementsNames, vector<string> & elementsValues){
    for(; substr_from_c_to_c(in, 0, 1, ' ', ')', false)!=" ";){
        string elementName=substr_from_c_to_c(in, 0, 1, ' ', ',', false);
        if(elementName=="/err"){
            elementName=substr_from_c_to_c(in, 0, 1, ' ', ')', false);
            erase_substr(in, elementName);
        }else{
            erase_substr(in, elementName+",");
        }
        elementsNames.push_back(elementName);
    }

    erase_substr(in, " ) values (");
    for(int i=0; substr_from_c_to_c(in, 0, 1, ' ', ')', false)!=" "; i++){
        string elementValue=substr_from_c_to_c(in, 0, 1, ' ', ',', false);
        if(elementValue=="/err"){
            elementValue=substr_from_c_to_c(in, 0, 1, ' ', ')', false);
            erase_substr(in, elementValue);
        }else{
            erase_substr(in, elementValue+",");
        }
        elementsValues.push_back(elementValue);
    }
}

bool Database::set_INSERT_INTO_data(string in, const int & Table_i, const vector<string> & elementsNames, const vector<string> & elementsValues){
    bool err=false;
    for(int i=0; i<elementsNames.size(); i++){
        int col_i=Tables[Table_i].find_col(elementsNames[i]);

        if(check_data_consistence(elementsValues[i], Tables[Table_i].elementsTypes[col_i])){

        } else{
            err=true;
        }
    }

}

int Database::find_Table(const string &in) {
    int i=0;
    bool found=false;
    for(; i<Tables.size() and !found; i++){
        if(Tables[i].get_name()==in){
            found=true;
        }
    }
    if(!found){
        return -1;
    } else{
        return i;
    }
}
