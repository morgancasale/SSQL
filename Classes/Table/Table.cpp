#include "Table.h"

bool Table::set_Table(const string &in){
    bool noErr=true;
    if(!control_create(in)){
        cerr<<endl<<"CREATE command syntax error!";
        noErr=false;
    } else{
        vector<string> data=get_CREATE_data(in);
        name=data[0];
        int dataSize=data.size();
        for(int i=1; i<(dataSize-1) and noErr; i++){
            noErr=!create_col(data[i], data);
        }
        noErr=find_check_primaryKey(data[dataSize-1]);
    }
    return noErr;
}

bool Table::find_check_primaryKey(const string & in){ //controlla se la chiave primaria ha senso e se esiste
    bool noErr=true;
    primaryKey_index=-1;

    if(in.find("primary key(")==-1){ noErr=false; }

    string key;
    if(noErr){
        key=substr_from_c_to_c(in, 1, 1, '(', ')');

        if (key == "/err") { noErr = false; }
    }

    if(noErr) {
        noErr = false;
        int i=0;
        for (const string &tmp : elementsNames) { if (key == tmp) { noErr = true; primaryKey_index=i; } i++; }
    }

    if(!noErr){
        cerr<<endl<<"Primary key is not valid or not found!";
    }
    return noErr;
}

bool Table::check_key(const string & key){ //controlla se non è già stato data questa key e se non è uguale ad un tipo o a /err
    bool noErr = true;
    bool existenceErr = false;
    if(key=="/err"){ noErr=false; }
    for(const string & tmp: allowed_coms){ if(key==tmp){ noErr=false; } }
    if(noErr){
        for(const string & tmp: allowed_types){ if(key==tmp){ noErr=false; } }
    }
    if(noErr){
        for(const string & tmp: elementsNames){ if(key==tmp){ noErr=false; existenceErr=true; } }
    }


    if(!noErr and !existenceErr){
        cerr<<endl<<"Column name ("<< key <<") is not valid, read the documentation to find out the allowed names";
    }
    else if(existenceErr){
        cerr<<endl<<"Column with name "<< key <<" already exists!";
    }
    return noErr;
}

bool Table::check_type(const string & type){
    bool noErr=false;
    for(const string & tmp: allowed_types){ if(tmp==type){ noErr=true; } }

    if(!noErr){
        cerr<<endl<<"Type "<< type <<" is not allowed!"<<endl;
        cerr<<"Check the documentation to find out the allowed types";
    }
    return noErr;
}

int Table::count_data(const vector<string> & data, const string & type){ //conta quanti dati di tipo "type" ci sono in data
    int counter=0;
    for(int i=1; i<data.size()-1; i++){
        string tmp=substr_from_c_to_c(data[i], 1, 2);
        if(tmp=="/err"){
            tmp=substr_from_c_to_c(data[i], 1, -1);
        }
        if(tmp==type){
            counter++;
        }
        if(tmp=="string" and type=="text"){
            counter++;
        }
    }
    return counter;
}

bool Table::create_col(string in, const vector<string> & data) {
    bool err=false;

    bool auto_increment=false;
    if(in.find("auto_increment")!=-1){
        auto_increment=true;
        erase_substr(in," auto_increment");
    }

    bool notNull=false;
    if(in.find("not null")!=-1){
        notNull=true;
        erase_substr(in," not null");
    }

    string key=substr_from_c_to_c(in, 0, 1);
    err=!check_key(key);

    string type;
    if(!err){
        type=substr_from_c_to_c(in, 1, -1);
        err=!check_type(type);
    }

    if((type!="int" and auto_increment)){
        if(!err){
            cerr<<endl<<"Type "<<type<<" doesn't support auto_increment parameter!";
            err=true;
        }
    }

    if(!err and type == "int"){
        auto * tmp2=new Column<int>;
        (*tmp2).key=key;
        (*tmp2).not_null=notNull;
        (*tmp2).auto_increment=auto_increment;
        cols.push_back(static_cast<void *>(tmp2));
    } else
    if(!err and type == "float"){
        auto * tmp2=new Column<float>;
        (*tmp2).key=key;
        (*tmp2).not_null=notNull;
        cols.push_back(static_cast<void *>(tmp2));
    } else
    if(!err and type == "char"){
        auto * tmp2=new Column<char>;
        (*tmp2).key=key;
        (*tmp2).not_null=notNull;
        cols.push_back(static_cast<void *>(tmp2));
    } else
    if(!err and (type == "string" or type == "text")){
        auto * tmp2=new Column<string>;
        (*tmp2).key=key;
        (*tmp2).not_null=notNull;
        cols.push_back(static_cast<void *>(tmp2));
    } else
    if(!err and type == "date") {
        auto * tmp2=new Column<Date>;
        (*tmp2).key=key;
        (*tmp2).not_null=notNull;
        cols.push_back(static_cast<void *>(tmp2));
    } else
    if(!err and type == "time"){
        auto * tmp2=new Column<Time>;
        (*tmp2).key=key;
        (*tmp2).not_null=notNull;
        cols.push_back(static_cast<void *>(tmp2));
    } else{
        err=true;
    }

    if(err){
        cerr<<endl<<"CREATE input syntax error!";
    }

    if(!err) {
        elementsTypes.push_back(type);
        elementsNames.push_back(key);
    }
    return err;
}

vector<string> Table::get_CREATE_data(string in){
    vector<string> data;
    data.resize(1);
    data[0]=substr_from_c_to_c(in, 0, 1);

    string line;
    for(int i=1; substr_from_c_to_c(in, 1, 1, '(', ')')!="  "; i++){//this checks if there is the final substring ");" somewhere
        data.resize(i+1);
        data[i]=substr_from_c_to_c(in, 2, 1, ' ', ',');
        if(data[i]=="/err"){
            data[i]=substr_from_c_to_c(in, 2, 7, ' ', ';');
            data[i].resize(data[i].size()-2);
            erase_substr(in, data[i]);
        }else{
            erase_substr(in, data[i]+", ");
        }

    }

    return data;
}

void Table::empty_table() {
    //for (int i = 0; i < cols.size(); i++)
        //static_cast<Column<typeof(string_to_type(elementsTypes[i]))> *>(cols[i])->values.resize(0);
}

int Table::find_col_by_name(const string &in) {
    int i=0;
    bool found=false;
    for(; i<elementsNames.size() and !found; i++){
        if(elementsNames[i]==in){
            found=true;
        }
    }
    if(!found){
        return -1;
    } else{
        return i-1;
    }
}

void Table::cast_data_to_col(const int & col_i, const string & type, const string & data){
    if(type=="int"){
        (*static_cast<Column<int>*>(cols[col_i])).values.push_back(stoi(data));
    } else
    if(type=="float"){
        (*static_cast<Column<float>*>(cols[col_i])).values.push_back(stof(data));
    } else
    if(type=="char"){
        (*static_cast<Column<char>*>(cols[col_i])).values.push_back(data[1]);
    } else
    if(type=="string" or type=="text"){
        string data_tmp=substr_from_c_to_c(data, 1, 2, '"', '"');
        (*static_cast<Column<string>*>(cols[col_i])).values.push_back(data_tmp);
    } else
    if(type=="time"){
        (*static_cast<Column<Time>*>(cols[col_i])).values.resize((*static_cast<Column<Time>*>(cols[col_i])).values.size()+1); //Increase Time vector of one
        (*static_cast<Column<Time>*>(cols[col_i])).values.end()->set_time(data);
    } else
    if(type=="date"){
        (*static_cast<Column<Date>*>(cols[col_i])).values.resize((*static_cast<Column<Date>*>(cols[col_i])).values.size()+1); //Increase Date vector of one
        (*static_cast<Column<Date>*>(cols[col_i])).values.end()->set_Date(data);
    }
}

bool Table::set_INSERT_INTO_data(const vector<string> & elements_Names, const vector<string> & elementsValues){
    bool err=false;
    if(elementsValues.size() != elements_Names.size()){
        if(elements_Names.size() > elementsValues.size()){
            cerr << endl << "Too few arguments in values where given!";
        } else{
            cerr << endl << "Too much arguments in values where given!";
        }
        err=true;
    }
    for(int i=0; i<elementsValues.size() and !err; i++){
        int col_i=find_col_by_name(elements_Names[i]);
        if(col_i!=-1) {
            string type;
            if(check_data_consistence(elementsValues[i], type=elementsTypes[col_i])) {
                cast_data_to_col(col_i, type, elementsValues[i]);
            } else{
                cerr<<endl<<"Some of the data is not compatible with the respective column!";
                err = true;
            }
        } else{
            cerr << endl << "No column with name " << elements_Names[i] << " is in the table!";
            err=true;
        }
    }
    return err;
}

void Table::auto_increment_col(){

    for(int i=0; i<cols.size(); i++){
        if(elementsTypes[i]=="int"){
            if((*static_cast<Column<int>*>(cols[i])).auto_increment){
                if(rows>0){
                    (*static_cast<Column<int>*>(cols[i])).values.resize((*static_cast<Column<int>*>(cols[i])).values.size()+1);
                    (*static_cast<Column<int>*>(cols[i])).values[(*static_cast<Column<int>*>(cols[i])).values.size()]++;
                } else {
                    if (!(*static_cast<Column<int> *>(cols[i])).not_null) {
                        (*static_cast<Column<int> *>(cols[i])).values[(*static_cast<Column<int> *>(cols[i])).values.size()] = 0;
                    }
                }
            }
        }
    }
}

bool Table::check_INSERT_INTO_data(const vector<string> &filled_elements) {
    bool fillErr=false, autoIncrAndNotNullErr=false;

    vector<string> notFilled= elementsNames - filled_elements;

    for(const string & emptyElement: notFilled){
        int j=find_col_by_name(emptyElement);
        if(elementsTypes[j]=="int"){
            if((*static_cast<Column<int>*>(cols[j])).key == emptyElement) {

                //se si sta riempendo la prima riga, e un int è "not null" e "auto_increment",
                //l'int va inizializzato per forza
                if (rows == 0) {
                    if ((*static_cast<Column<int> *>(cols[j])).not_null and
                        (*static_cast<Column<int> *>(cols[j])).auto_increment) {
                        autoIncrAndNotNullErr = true;
                    }
                }

                if ((*static_cast<Column<int> *>(cols[j])).not_null and
                    !(*static_cast<Column<int> *>(cols[j])).auto_increment) {
                    fillErr = true;
                }

            }

        } else
        if(elementsTypes[j]=="float"){
            if((*static_cast<Column<float>*>(cols[j])).key == emptyElement and
               (*static_cast<Column<float>*>(cols[j])).not_null){
                fillErr=true;
            }
        } else
        if(elementsTypes[j]=="char"){
            if((*static_cast<Column<char>*>(cols[j])).key == emptyElement and
               (*static_cast<Column<char>*>(cols[j])).not_null){
                fillErr=true;
            }
        } else
        if(elementsTypes[j]=="string"){
            if((*static_cast<Column<char>*>(cols[j])).key == emptyElement and
               (*static_cast<Column<char>*>(cols[j])).not_null){
                fillErr=true;
            }
        } else
        if(elementsTypes[j]=="time"){
            if((*static_cast<Column<Time>*>(cols[j])).key == emptyElement and
               (*static_cast<Column<Time>*>(cols[j])).not_null){
                fillErr=true;
            }
        } else
        if(elementsTypes[j]=="date"){
            if((*static_cast<Column<Date>*>(cols[j])).key == emptyElement and
               (*static_cast<Column<Date>*>(cols[j])).not_null){
                fillErr=true;
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
}

int Table::get_col_index(const string & in){ //returns 1 if no element with that name is found
    int index=-1;
    for(int i=0; i<elementsNames.size(); i++){
        if(elementsNames[i]==in){ index=i; }
    }
    return index;
}

bool Table::find_Rows_by_value(const string &data, const int & col_i, vector<int> &foundRows) {
    bool noErr=true;
    return noErr;
}