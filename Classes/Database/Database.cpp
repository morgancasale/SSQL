#include "Database.h"

bool Database::check_TableName(const string & name){
    bool noErr=true;
    for(const string & tmp: allowed_coms){ noErr=(name!=tmp); }
    if(noErr){ for(const string & tmp: allowed_types){ noErr=(name!=tmp); } }
    if(noErr){ if(name=="/err"){ noErr=false; } }
    return noErr;
}

bool Database::check_Table(const string &in, const bool show_err) {
    bool noErr;
    string in_Table_name=substr_from_c_to_c(in,2,3);
    noErr=check_TableName(in_Table_name);
    int i=0;
    if(!Tables.empty()) {
        do {
            if (Tables[i].get_name() == in_Table_name) {
                noErr = false;
            }
            i++;
        } while ((i < Tables.size()) and noErr);
    }
    if(!noErr and show_err){
        cerr<<"Table named"<<in_Table_name<<" already exists!"<<endl;
        cerr<<"Choose another name.";
    }

    return noErr;
}

bool Database::process_command(const string &choice, const string &command) {
    bool noErr=true;  int j=0;
    if(command=="quit()"){
        //stampa su file il database
    } else
    if(command=="create table"){
        if(check_Table(choice, true)){
            Table temp;//this creates a temporary Table
            if(temp.set_Table(choice)){
                Tables.push_back(temp);
                cout<<"a";
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
       //delete_Row_from_Table(choice);
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

    string Table=substr_from_c_to_c(in, 0, 1, ' ', ' ', false);
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
    for(; !substr_from_c_to_c(in, 1, 1, '(', ')', false).empty();){
        string elementName=substr_from_c_to_c(in, 1, 1, '(', ',', false);
        if(elementName=="/err" or num_of_words(elementName)>1){
            elementName=substr_from_c_to_c(in, 1, 1, '(', ')', false);
            erase_substr(in, elementName);
        }else{
            erase_substr(in, elementName+", ");
        }
        elementsNames.push_back(elementName);
    }

    in-="() values (";
    for(int i=0; !substr_from_c_to_c(in, 0, 1, ' ', ')', false).empty(); i++){
        string elementValue=substr_from_c_to_c(in, 0, 1, ' ', ',', false);
        if(elementValue=="/err"){
            elementValue=substr_from_c_to_c(in, 0, 1, ' ', ')', false);
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

/*bool Database::cast_data(Table & table, const int & Table_i, const int & col_i, const string & type, const string & data){
    bool auto_increment_err=false;
    if(type=="int"){
        if(Tables[Tarows==0)
        if((*static_cast<Column<int>*>(table.cols[col_i])).auto_increment){ //non puoi inserire dati in una colonna auto_increment
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
}*/

/*bool Database::check_INSERT_INTO_data(const int & Table_i, const vector<string> & filled_elements){
    bool fillErr=false, autoIncrAndNotNullErr=false;

    vector<string> not_filled=Tables[Table_i].elementsNames-filled_elements;

    for(int i=0; i<Tables[Table_i].cols.size(); i++){
        for(const string & emptyElement: not_filled){
            if(Tables[Table_i].elementsTypes[i]=="int"){
                if((*static_cast<Column<int>*>(Tables[Table_i].cols[i])).key == emptyElement) {

                    //se si sta riempendo la prima riga, e un int è "not null" e auto_increment,
                    //l'int va inizializzato per forza
                    if (Tables[Table_i].rows == 0) {
                        if ((*static_cast<Column<int> *>(Tables[Table_i].cols[i])).not_null and
                            (*static_cast<Column<int> *>(Tables[Table_i].cols[i])).auto_increment) {
                            autoIncrAndNotNullErr = true;
                        }
                    }

                    if ((*static_cast<Column<int> *>(Tables[Table_i].cols[i])).not_null and
                        !(*static_cast<Column<int> *>(Tables[Table_i].cols[i])).auto_increment) {
                        fillErr = true;
                    }

                }

            } else
            if(Tables[Table_i].elementsTypes[i]=="float"){
                if((*static_cast<Column<float>*>(Tables[Table_i].cols[i])).key == emptyElement and
                   (*static_cast<Column<float>*>(Tables[Table_i].cols[i])).not_null){
                    fillErr=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="char"){
                if((*static_cast<Column<char>*>(Tables[Table_i].cols[i])).key == emptyElement and
                   (*static_cast<Column<char>*>(Tables[Table_i].cols[i])).not_null){
                    fillErr=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="string"){
                if((*static_cast<Column<char>*>(Tables[Table_i].cols[i])).key == emptyElement and
                   (*static_cast<Column<char>*>(Tables[Table_i].cols[i])).not_null){
                    fillErr=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="time"){
                if((*static_cast<Column<Time>*>(Tables[Table_i].cols[i])).key == emptyElement and
                   (*static_cast<Column<Time>*>(Tables[Table_i].cols[i])).not_null){
                    fillErr=true;
                }
            } else
            if(Tables[Table_i].elementsTypes[i]=="date"){
                if((*static_cast<Column<Date>*>(Tables[Table_i].cols[i])).key == emptyElement and
                   (*static_cast<Column<Date>*>(Tables[Table_i].cols[i])).not_null){
                    fillErr=true;
                }
            }
        }
    }

    if(autoIncrAndNotNullErr){
        cerr<<endl<<R"(An element set as "not null" and "auto_increment" wasn't initialized in the first row!)";
    }

    if(fillErr){
        cerr<<endl<<R"(An element set as "not null" was not filled!)";
    }
    return (fillErr and autoIncrAndNotNullErr);
}*/

/*void Database::auto_increment(const int & Table_i){
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
}*/

/*bool Database::set_INSERT_INTO_data(const int & Table_i, const vector<string> & elementsNames, const vector<string> & elementsValues){
    bool err=false;
    for(int i=0; i<elementsNames.size(); i++){
        int col_i=Tables[Table_i].find_col_by_name(elementsNames[i]);
        if(col_i!=-1) {
            string type;
            if(check_data_consistence(elementsValues[i], type=Tables[Table_i].elementsTypes[col_i])) {
                Tables[i].cast_data_to_col(col_i, type, elementsValues[i]);
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
}*/