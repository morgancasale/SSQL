#include "Database.h"

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
    bool err=true;  int j=0;
    if(command=="quit()"){
    } else
    if(command=="create table"){
        if(check_Table(choice, true)){
            Table temp(choice); //this creates a temporary Table
            Tables.resize(Tables.size()+1);
            Tables[Tables.size()]=temp; //that is copied to the last ( == new ) Table of the Database
        }
    } else
    if(command=="drop table" and control_drop(choice)){
        for(int i=0; i<Tables.size(); i++){
            if(Tables[i].get_name() == choice)  err=false;   j=i;
        }
        if(!err) Tables.erase(Tables.begin()+j);
        else     cerr<<"la tabella non esiste"<<endl;
    } else
    if(command=="truncate table" and control_truncate(choice)){
        for(int i=0; i<Tables.size(); i++){
            if(Tables[i].get_name() == choice)  err=false;   j=i;
        }
        if(!err)    Tables[j].empty_table();
        else cerr<<"la tabella non esiste"<<endl;
    } else
    if(command=="insert into") {
        //add_Row_to_Table(choice);
    } else
    if(command=="delete from"){
       //delete_Row_from_Table(choice);
    } else
    if(command=="update"){
        //update_Row_data(choice);
    } else
    if(command=="select"){
        //print_selected_data(choice);
    }
    return err;
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

bool Database::check_not_filled(const int & Table_i, const vector<string> & filled_elements){
    bool err=false;
    vector<string> not_filled=Tables[Table_i].elementsNames-filled_elements;

    for(int i=0; i<Tables[Table_i].cols.size(); i++){
        for(const string & el: not_filled){
            if(Tables[Table_i].elementsTypes[i]=="int"){
                if((*static_cast<Column<int>*>(Tables[Table_i].cols[i])).key==el and
                   (*static_cast<Column<int>*>(Tables[Table_i].cols[i])).not_null){
                    err=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="float"){
                if((*static_cast<Column<float>*>(Tables[Table_i].cols[i])).key==el and
                   (*static_cast<Column<float>*>(Tables[Table_i].cols[i])).not_null){
                    err=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="char"){
                if((*static_cast<Column<char>*>(Tables[Table_i].cols[i])).key==el and
                   (*static_cast<Column<char>*>(Tables[Table_i].cols[i])).not_null){
                    err=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="string"){
                if((*static_cast<Column<char>*>(Tables[Table_i].cols[i])).key==el and
                   (*static_cast<Column<char>*>(Tables[Table_i].cols[i])).not_null){
                    err=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="time"){
                if((*static_cast<Column<Time>*>(Tables[Table_i].cols[i])).key==el and
                   (*static_cast<Column<Time>*>(Tables[Table_i].cols[i])).not_null){
                    err=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="date"){
                if((*static_cast<Column<Date>*>(Tables[Table_i].cols[i])).key==el and
                   (*static_cast<Column<Date>*>(Tables[Table_i].cols[i])).not_null){
                    err=true;
                }
            }
        }
    }

    if(err){
        cerr<<endl<<"An element set as not null was not filled!";
    }
    return err;
}

void Database::auto_increment(const int & Table_i){
    for(int i=0; i<Tables[Table_i].cols.size(); i++){
        if(Tables[Table_i].elementsTypes[i]=="int"){
            if((*static_cast<Column<int>*>(Tables[Table_i].cols[i])).auto_increment){
                (*static_cast<Column<int>*>(Tables[Table_i].cols[i])).values.resize((*static_cast<Column<int>*>(Tables[Table_i].cols[i])).values.size()+1);
                if(Table_i>0){
                    (*static_cast<Column<int>*>(Tables[Table_i].cols[i])).values[(*static_cast<Column<int>*>(Tables[Table_i-1].cols[i])).values.size()]++;
                } else{
                    (*static_cast<Column<int>*>(Tables[Table_i].cols[i])).values[(*static_cast<Column<int>*>(Tables[Table_i-1].cols[i])).values.size()]=0;
                }
            }
        }
    }
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
        err=set_INSERT_INTO_data(Table_i, elementsNames, elementsValues);
        err=check_not_filled(Table_i, elementsNames);
        if(!err){
            auto_increment(Table_i);
        }

    } else{
        cerr<<endl<<"There is no Table with name "<<Table<<"!";
        err=true;
    }
    return err;
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



bool Database::set_INSERT_INTO_data(const int & Table_i, const vector<string> & elementsNames, const vector<string> & elementsValues){
    bool err=false;
    for(int i=0; i<elementsNames.size(); i++){
        int col_i=Tables[Table_i].find_col_by_name(elementsNames[i]);
        if(col_i!=-1) {
            string type;
            if(check_data_consistence(elementsValues[i], type=Tables[Table_i].elementsTypes[col_i])) {
                err=cast_data(Tables[i], col_i, type, elementsValues[i]);
            } else{
                cerr<<endl<<"Some of the data is not compatible with the respective column!";
                err = true;
            }
        } else{
            cerr<<endl<<"No column with name "<<elementsNames[i]<<" is in the table!";
            err=true;
        }
    }
    return err;
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

bool Database::cast_data(Table & table, const int & col_i, const string & type, const string & data){
    bool auto_increment_err=false;
    if(type=="int"){
        if((*static_cast<Column<int>*>(table.cols[col_i])).auto_increment){
            auto_increment_err=true;
        } else{
            (*static_cast<Column<int>*>(table.cols[col_i])).values.push_back(stoi(data));
        }
    } else
    if(type=="float"){
        (*static_cast<Column<float>*>(table.cols[col_i])).values.push_back(stof(data));
    } else
    if(type=="char"){
        (*static_cast<Column<char>*>(table.cols[col_i])).values.push_back(data[1]);
    } else
    if(type=="string"){
        string data_tmp=substr_from_c_to_c(data, 1, 2, '"', '"', false);
        (*static_cast<Column<string>*>(table.cols[col_i])).values.push_back(data_tmp);
    } else
    if(type=="time"){
        (*static_cast<Column<Time>*>(table.cols[col_i])).values.resize((*static_cast<Column<Time>*>(table.cols[col_i])).values.size()+1); //Increase Time vector of one
        (*static_cast<Column<Time>*>(table.cols[col_i])).values.end()->set_time(data);
    } else
    if(type=="date"){
        (*static_cast<Column<Date>*>(table.cols[col_i])).values.resize((*static_cast<Column<Date>*>(table.cols[col_i])).values.size()+1); //Increase Date vector of one
        (*static_cast<Column<Date>*>(table.cols[col_i])).values.end()->set_Date(data);
    }

    if(auto_increment_err){
        cerr<<endl<<"It isn't possible to enter data in a column if auto_increment was chosen for it!";
    }
    return auto_increment_err;
}