#include "Database.h"

bool Database::check_TableName(const string & name){
    bool noErr=true;
    for(const string & tmp: allowed_coms){ noErr=(name!=tmp); }
    if(noErr){ for(const string & tmp: allowed_types){ noErr=(name!=tmp); } }
    if(noErr){ for(const string & tmp: reserved_words){ noErr=(name!=tmp); } }
    return noErr;
}

//if existence parameter is true the function checks if the table exists, else if doesn't exist
bool Database::check_Table_existence(string in_Table_name, const bool & existence){
    bool not_exists=true;
    int i=0;
    if(!Tables.empty()) {
        do {
            string tmp=Tables[i].get_name();
            if ( tolower(tmp) == tolower(in_Table_name)) {
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
    if(command=="drop table"){
        if((noErr=control_drop(choice))){
            noErr=DROP_TABLE(choice);
        }
    } else
    if(command=="truncate table" and control_truncate(choice)){
        if((noErr=control_truncate(choice))){
            noErr=TRUNCATE_TABLE(choice);
        }
    } else
    if(command=="insert into") {
        if((noErr=control_insert(choice))){
            noErr=!INSERT_INTO(choice);
        }
    } else
    if(command=="delete"){
       if((noErr=control_delete(choice))){
           noErr=DELETE(choice);
       }
    } else
    if(command=="update"){
        if((noErr=control_update(choice))){
            noErr=UPDATE(choice);
        }
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

    string Table=substr_from_c_to_c(in, 0, 1, ' ', '(');
    in-=Table;
    replace_chars(Table,{' '}, -1);
    int Table_i=find_Table(Table);

    if(Table_i!=-1) {
        vector<string> elementsNames;
        vector<string> elementsValues;
        err=!get_INSERT_INTO_data(in, elementsNames, elementsValues);
        if(!err){ err=Tables[Table_i].set_INSERT_INTO_data(elementsNames, elementsValues); }
        if(!err){
            err= Tables[Table_i].checkINSERT_INTOData_and_Nullify(elementsNames);
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

bool Database::get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues) {
    bool noErr=true;
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
    for(int i=0; !substr_from_c_to_c(in, 0, 1, ' ', ')').empty() and noErr; i++){
        string elementValue=substr_from_c_to_c(in, 0, 1, ' ', ',');
        if(elementValue=="/err"){
            elementValue=substr_from_c_to_c(in, 0, 1, ' ', ')');
            erase_substr(in, elementValue);
        }else{
            erase_substr(in, elementValue+", ");
        }
        for(const string & tmp: reserved_words){ if(elementValue==tmp){ noErr=false; } }
        if(noErr){
            elementsValues.push_back(elementValue);
        } else{
           cerr<<endl<<"A reserved word ( "<<elementValue<<" ) was inserted!";
        }
    }
    return noErr;
}

int Database::find_Table(string in) {
    int i=0;
    bool found=false;
    for(; i<Tables.size() and !found; i++){
        string tmp=Tables[i].get_name();
        if(tolower(tmp)==tolower(in)){
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
    string table_name=substr_from_c_to_c(in, 0, 1);
    bool noErr=!check_Table_existence(table_name, true);
    int table_i=find_Table(table_name);

    if(noErr) {
        string element = substr_from_s_to_s(in,"where ","=");
        replace_chars(element, {' '}, -1);
        int col_i;
        if ((col_i=Tables[table_i].get_col_index(element))==-1) {
            cerr<<"No colum with name "<<element<<" was found!";
            noErr = false;
        }
        if(noErr){
            string data = substr_from_c_to_c(in, 1, 1, '=', ';');
            vector<int> foundRows;
            noErr=Tables[table_i].find_Rows_by_value(data, col_i, foundRows);
            if(noErr){
                Tables[table_i].deleteRows(foundRows);
            }
        }

    }
    return noErr;
}

bool Database::DROP_TABLE(const string & in){
    bool noErr=true;
    string tableName=in-";";
    noErr=!check_Table_existence(tableName, true);
    if(!noErr){
        cerr<<endl<<"No Table named "<<tableName<<" was found!";
    } else{
        int Table_i=find_Table(tableName);
        Table & table=Tables[Table_i];
        for(int i=table.elementsTypes.size(); i>0; i--){
            table.clear_col(i);
            table.elementsTypes.resize(table.elementsTypes.size()-1);
        }
        deleteElements_from_vec(Tables,{Table_i});
    }
    return noErr;
}

bool Database::TRUNCATE_TABLE(const string & in){
    bool noErr=true;
    string tableName=in-";";
    noErr=!check_Table_existence(tableName, true);
    if(!noErr){
        cerr<<endl<<"No Table named "<<tableName<<" was found!";
    } else{
        int Table_i=find_Table(tableName);
        Table & table=Tables[Table_i];
        table.empty_content();
    }
    return noErr;
}

bool Database::UPDATE(string in){
    bool noErr;
    string tableName=substr_from_c_to_c(in, 0, 1);
    noErr=!check_Table_existence(tableName, true);
    Table & table=Tables[find_Table(tableName)];

    if(noErr){
        in-=(tableName+" set ");

        string colToSearch= substr_from_s_to_s(in, "where ", "=", true);
        replace_chars(colToSearch, {' '}, -1);
        int col_index;
        noErr=((col_index=table.get_col_index(colToSearch))!=-1);

        if(noErr){
            string searchData= substr_from_s_to_s(in, colToSearch, ";");
            searchData=substr_from_c_to_c(searchData, 1, -1, '=', ' ');
            replace_chars(searchData, {' '}, -1);

            vector<int> foundRows;
            noErr=table.find_Rows_by_value(searchData, col_index, foundRows);
            in-=(substr_from_s_to_s(in, " where", ";")+";");
            if(noErr){
                replace_chars(in, {' '}, -1);
                vector<string> updateData;
                for(; substr_from_c_to_c(in,0,-1)!="/err";){
                    string tmp=substr_from_c_to_c(in, 0, 1, ' ', ',');
                    tmp+=",";
                    if(tmp=="/err,"){
                        tmp=substr_from_c_to_c(in, 0,-1);
                    }
                    in-=tmp;
                    if(tmp.find(',')){ tmp-=","; }
                    updateData.push_back(tmp);

                }
                noErr= table.set_UPDATE_data(updateData, foundRows);
            } else{
                cerr<<"No row containing"<<searchData<<"was found!";
            }

        } else{
            cerr<<endl<<"No column "<<colToSearch<<"was found!";
        }

    } else{
        cerr<<"Table named "<<tableName<<" doesn't exist!";
    }
    return noErr;
}