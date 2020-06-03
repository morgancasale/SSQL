#include "Database.h"

bool Database::check_TableName(const string & name){
    bool noErr=true;
    for(const string & tmp: allowed_coms){ noErr=(name!=tmp); }
    if(noErr){ for(const string & tmp: allowed_types){ noErr=(name!=tmp); } }
    if(noErr){ if(name=="/err"){ noErr=false; } }
    return noErr;
}

//if existence parameter is true the function checks if the table exists, else if doesn't exist
bool Database::check_Table_existence(const string &in_Table_name, const bool & existence){
    bool not_exists=true;
    int i=0;
    if(!Tables.empty()) {
        do {
            if (Tables[i].get_name() == in_Table_name) {
                not_exists = false;
            }
            i++;
        } while ((i < Tables.size()) and not_exists);
    }
    if(!existence and !not_exists){ //se devo controllare che esista e non esiste
        cerr<<"Table named"<<in_Table_name<<" already exists!"<<endl;
        cerr<<"Choose another name.";
    }
    if(!existence and !not_exists){ //se devo controllare che non esista ed esiste
        cerr<<"Table named "<<in_Table_name<<" doesn't exist!"<<endl;
    }

    return not_exists;
}

bool Database::process_command(const string &choice, const string &command) {
    bool noErr=true;  int j=0;
    if(command=="quit()"){
        //stampa su file il database
    } else
    if(command=="create table"){
        string table_name=substr_from_c_to_c(choice, 0, 1);
        noErr=check_TableName(table_name);
        if(check_Table_existence(table_name, false) and noErr){
            Table temp;//this creates a temporary Table
            if(temp.set_Table(choice)){
                Tables.push_back(temp);
            }
            else{
                noErr=false;
            }
        }
    } else
    if(command=="drop table" and control_drop(choice)){
        noErr=false;
        for(int i=0; i<Tables.size(); i++){
            if(Tables[i].get_name() == choice)  noErr=true;   j=i;
        }
        if(noErr) Tables.erase(Tables.begin()+j);
        else     cerr<<"la tabella non esiste"<<endl;
    } else
    if(command=="truncate table" and control_truncate(choice)){
        noErr=false;
        for(int i=0; i<Tables.size(); i++){
            if(Tables[i].get_name() == choice)  noErr=true;   j=i;
        }
        if(noErr)    Tables[j].empty_table();
        else cerr<<"la tabella non esiste"<<endl;
    } else
    if(command=="insert into") {
        if(control_insert(choice)){
            INSERT_INTO(choice);
        }
        else{
            noErr=false;
        }
    } else
    if(command=="delete from"){
       if(control_delete(choice)){
           DELETE(choice);
       }
    } else
    if(command=="update"){
        //update_Row_data(choice);
    } else
    if(command=="select"){
        //print_selected_data(choice);
    }
    return noErr;
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
    bool err;

    string Table=substr_from_c_to_c(in, 0, 1, ' ', ' ');
    in-=(Table+" ");
    int Table_i=find_Table(Table);

    if(Table_i!=-1) {
        vector<string> elementsNames;
        vector<string> elementsValues;
        get_INSERT_INTO_data(in, elementsNames, elementsValues);
        err=Tables[Table_i].set_INSERT_INTO_data(elementsNames, elementsValues);
        if(!err){
            err=Tables[Table_i].check_INSERT_INTO_data(elementsNames);
        }
        if(!err){
            Tables[Table_i].auto_increment_col();
        }
        Tables[Table_i].rows++;
    } else{
        cerr<<endl<<"There is no Table with name "<<Table<<"!";
        err=true;
    }
    return err;
}

void Database::get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues) {
    for(; !substr_from_c_to_c(in, 1, 1, '(', ')').empty();){
        string elementName=substr_from_c_to_c(in, 1, 1, '(', ',');
        if(elementName=="/err" or num_of_words(elementName)>1){
            elementName=substr_from_c_to_c(in, 1, 1, '(', ')');
            erase_substr(in, elementName);
        }else{
            erase_substr(in, elementName+", ");
        }
        elementsNames.push_back(elementName);
    }

    in-="() values (";
    for(int i=0; !substr_from_c_to_c(in, 0, 1, ' ', ')').empty(); i++){
        string elementValue=substr_from_c_to_c(in, 0, 1, ' ', ',');
        if(elementValue=="/err"){
            elementValue=substr_from_c_to_c(in, 0, 1, ' ', ')');
            erase_substr(in, elementValue);
        }else{
            erase_substr(in, elementValue+", ");
        }
        elementsValues.push_back(elementValue);
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
        return i-1;
    }
}

bool Database::DELETE(string in) {
    bool noErr=true;

    string table_name=substr_from_c_to_c(in, 2, 3);
    noErr=check_Table_existence(table_name, true);
    int table_i=find_Table(table_name);

    string element=substr_from_c_to_c(in, 4, 1, ' ', '=');
    if(Tables[table_i].check_element_existence(element))

    string data=substr_from_c_to_c(in, 1, 1, '=', ';');
    return noErr;
}