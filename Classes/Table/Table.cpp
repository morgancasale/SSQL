#include <memory>
#include "Table.h"

/*template<typename type>
void Column<type>::printCol_to_file(ofstream & out) {
    out<<key<<" ";
    out<<not_null<<" ";
    out<<auto_increment<<endl;
    for(type value: values){

        out<<to_string(value)<<" ";
    }
    out<<endl;

    for(bool nullity: valuesNullity){
        out<<nullity<<" ";
    }
    out<<endl;
}*/

bool Table::set_Table(const string &in){
    bool noErr=true;
    vector<string> data = get_CREATE_data(in);
    noErr = control_CREATE_data(data);
    if (noErr) {
        name = data[0];
        int dataSize = data.size();
        for (int i = 1; i < (dataSize - 1) and noErr; i++) {
            noErr = !create_col(data[i], false);
        }
        noErr = find_check_primaryKey(data[dataSize - 1]);
    } else {
        cerr << endl << "Forbidden names were given to the columns!";
    }
    return noErr;
}

bool Table::find_check_primaryKey(const string & in){ //controlla se la chiave primaria ha senso e se esiste
    bool noErr=true;
    primaryKey_index=-1;
    if(in.find("primary key(")==-1 and in.find("primary key (")==-1){ noErr=false; }

    string key;
    if(noErr){
        key= substr_CC(in, 1, 1, '(', ')');

        if (key == "/err") { noErr = false; }
    }

    if(noErr) {
        noErr = false;
        for (int i=0; i<elementsNames.size() and !noErr; i++) {
            string tmp=elementsNames[i];
            if (key == tmp) { noErr = true; primaryKey_index=i; }
        }
    }

    if(!noErr){
        cerr<<endl<<"Primary key is not valid or not found!";
    }
    return noErr;
}

bool Table::check_key(const string &key, const bool &existence) { //controlla se non è già stato data questa key e se non è uguale ad un tipo o a /err
    bool noErr = true;
    bool existenceErr = false;
    if(key=="/err"){ noErr=false; }
    for(const auto & allowed_com : allowed_coms){ if(key==allowed_com){ noErr=false; } }
    if(noErr){
        for(const auto & allowed_type : allowed_types){ if(key==allowed_type){ noErr=false; } }
    }
    if(noErr and !existence){
        for(auto & elementsName : elementsNames){ if(key==elementsName){ noErr=false; existenceErr=true; } }
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
        string tmp= substr_CC(data[i], 1, 2);
        if(tmp=="/err"){
            tmp= substr_CC(data[i], 1, -1);
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

bool Table::create_col(string in, const bool &key_existence) {
    bool err=false;

    bool auto_increment=false;
    if(in.find("auto_increment")!=-1){
        auto_increment=true;
        in-=" auto_increment";
    }

    bool notNull=false;
    if(in.find("not null")!=-1){
        notNull=true;
        in-=" not null";
    }

    string key= substr_CC(in, 0, 1);
    replace_chars(key, {' '}, -1);
    err=!check_key(key, key_existence);
    in-=key;

    string type;
    if(!err){
        type= substr_CC(in, 0, -1);
        replace_chars(type, {' '}, -1);
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

    if(!err and !key_existence) {
        elementsTypes.push_back(type);
        elementsNames.push_back(key);
    }
    return err;
}

vector<string> Table::get_CREATE_data(string in){
    vector<string> data;
    data.resize(1);
    data[0]= substr_CC(in, 0, 1);

    string line;
    for(int i=1; substr_CC(in, 1, 1, '(', ';') != ")"; i++){//this checks if there is the final substring ");" somewhere
        data.resize(i+1);
        data[i]= substr_CC(in, 1, 1, '(', ',');
        if(data[i]=="/err"){
            data[i]= substr_CC(in, 1, 1, '(', ';');
            data[i].resize(data[i].size()-1);
            erase_substr(in, data[i]);
            removeSpaces_fromStart_andEnd(data[i]);
        }else{
            erase_substr(in, data[i]+", ");
        }
        removeSpaces_fromStart_andEnd(data[i]);
        remove_duplicate_chars(in, {' '});

    }

    return data;
}

int Table::find_col_by_name(string in) {
    int i=0;
    bool found=false;
    for(; i<elementsNames.size() and !found; i++){
        string tmp=elementsNames[i];
        if(tmp==in){
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
        Column<int> & tmp=(*static_cast<Column<int>*>(cols[col_i]));
        tmp.values.push_back(stoi(data));
        tmp.valuesNullity.push_back(false);
        int a=0;
    } else
    if(type=="float"){
        Column<float> & tmp=(*static_cast<Column<float>*>(cols[col_i]));
        tmp.values.push_back(stof(data));
        tmp.valuesNullity.push_back(false);
        int a=0;
    } else
    if(type=="char"){
        Column<char> & tmp=(*static_cast<Column<char>*>(cols[col_i]));
        tmp.values.push_back(data[1]);
        tmp.valuesNullity.push_back(false);
        int a=0;
    } else
    if(type=="string" or type=="text"){
        Column<string> & tmp=(*static_cast<Column<string>*>(cols[col_i]));
        tmp.values.push_back(data);
        tmp.valuesNullity.push_back(false);
        int a=0;
    } else
    if(type=="time"){
        Column<Time> & tmp=(*static_cast<Column<Time>*>(cols[col_i]));
        tmp.values.resize((*static_cast<Column<Time>*>(cols[col_i])).values.size()+1); //Increase Time vector of one
        tmp.values.end()->set_time(data);
        tmp.valuesNullity.push_back(false);
        int a=0;
    } else
    if(type=="date"){
        Column<Date> & tmp=(*static_cast<Column<Date>*>(cols[col_i]));
        tmp.values.resize((*static_cast<Column<Date>*>(cols[col_i])).values.size()+1); //Increase Date vector of one
        tmp.values.end()->set_Date(data);
        tmp.valuesNullity.push_back(false);
        int a=0;
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
            Column<int> &tmp = (*static_cast<Column<int> *>(cols[i]));
            if (tmp.values.size() < (rows + 1)){
                if (tmp.auto_increment and rows > 0){
                    if(tmp.values[tmp.values.size() - 1]>0){
                        tmp.values.push_back(tmp.values[tmp.values.size() - 1] + 1);
                    } else{
                        tmp.values.push_back(-(abs(tmp.values[tmp.values.size() - 1])+ 1));
                    }
                } else{
                    tmp.values.resize(tmp.values.size() + 1);
                }
            }
        }
    }
}

bool Table::checkINSERT_INTOData_and_Nullify(vector<string> filled_elements) {
    //Column<string> & col=(*static_cast<Column<string> *>(cols[0]));
    bool fillErr=false, autoIncrAndNotNullErr=false;
    vector<string> elements=elementsNames;
    for(auto & element : elements){ tolower(element);}
    for(auto & filled_element : filled_elements){ tolower(filled_element); }
    vector<string> notFilled= elements - filled_elements;

    for(const string & emptyElement: notFilled){
        int j=find_col_by_name(emptyElement);
        if(elementsTypes[j]=="int"){
            Column<int> & tmp=(*static_cast<Column<int>*>(cols[j]));
            if(tmp.key == emptyElement) {

                //se si sta riempendo la prima riga, e un int è "not null" e "auto_increment",
                //l'int va inizializzato per forza
                if (rows == 0) {
                    if (tmp.not_null and tmp.auto_increment) {
                        autoIncrAndNotNullErr = true;
                    }
                }

                if (tmp.not_null and !tmp.auto_increment) {
                    fillErr = true;
                }

                if(!(fillErr and autoIncrAndNotNullErr)){
                    tmp.valuesNullity.push_back(true);
                    int a=0;
                }
            }
            if(tmp.values.size()!=tmp.valuesNullity.size()){
                tmp.values.resize(tmp.valuesNullity.size());
            }
        } else
        if(elementsTypes[j]=="float"){
            Column<float> & tmp=(*static_cast<Column<float>*>(cols[j]));
            if(tmp.key == emptyElement and tmp.not_null){
                fillErr=true;
            }
            if(!fillErr){
                tmp.valuesNullity.push_back(true);
            }
            if(tmp.values.size()!=tmp.valuesNullity.size()){
                tmp.values.resize(tmp.valuesNullity.size());
            }
        } else
        if(elementsTypes[j]=="char"){
            Column<char> & tmp=(*static_cast<Column<char>*>(cols[j]));
            if(tmp.key == emptyElement and tmp.not_null){
                fillErr=true;
            }
            if(!fillErr){
                tmp.valuesNullity.push_back(true);
            }
            if(tmp.values.size()!=tmp.valuesNullity.size()){
                tmp.values.resize(tmp.valuesNullity.size());
            }
        } else
        if(elementsTypes[j]=="string" or elementsTypes[j]=="text"){
            Column<string> & tmp=(*static_cast<Column<string>*>(cols[j]));
            if(tmp.key == emptyElement and tmp.not_null){
                fillErr=true;
            }
            if(!fillErr){
                tmp.valuesNullity.push_back(true);
            }
            if(tmp.values.size()!=tmp.valuesNullity.size()){
                tmp.values.resize(tmp.valuesNullity.size());
            }
        } else
        if(elementsTypes[j]=="time"){
            Column<Time> & tmp=(*static_cast<Column<Time>*>(cols[j]));
            if(tmp.key == emptyElement and tmp.not_null){
                fillErr=true;
            }
            if(!fillErr){
                tmp.valuesNullity.push_back(true);
            }
            if(tmp.values.size()!=tmp.valuesNullity.size()){
                tmp.values.resize(tmp.valuesNullity.size());
            }
        } else
        if(elementsTypes[j]=="date"){
            Column<Date> & tmp=(*static_cast<Column<Date>*>(cols[j]));
            if(tmp.key == emptyElement and tmp.not_null){
                fillErr=true;
            }
            if(!fillErr){
                tmp.valuesNullity.push_back(true);
            }
            if(tmp.values.size()!=tmp.valuesNullity.size()){
                tmp.values.resize(tmp.valuesNullity.size());
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

int Table::get_col_index(const string & in){ //returns -1 if no element with that name is found
    int index=-1;
    for(int i=0; i<elementsNames.size(); i++){
        if(elementsNames[i]==in){ index=i; }
    }
    return index;
}

bool Table::find_Rows_by_value(string data1, const int & col_i, vector<int> &foundRows, const string & op, string data2= "/err") {
    bool noErr=true;
    const string & type=elementsTypes[col_i];
    noErr=check_data_consistence(data1, type);

    if(noErr) {
        if (elementsTypes[col_i] == "int") {
            vector<int> tmp = (*static_cast<Column<int> *>(cols[col_i])).values;
            for (int i = 0; i < tmp.size(); i++) {
                if (op == "=" and to_string(tmp[i]) == data1)
                    foundRows.push_back(i);
                else if (op == ">" and to_string(tmp[i]) > data1)
                    foundRows.push_back(i);
                else if (op == "<" and to_string(tmp[i]) < data1)
                    foundRows.push_back(i);
                else if (op == ">=" and to_string(tmp[i]) >= data1)
                    foundRows.push_back(i);
                else if (op == "<=" and to_string(tmp[i]) <= data1)
                    foundRows.push_back(i);
                else if (op == "<>" and to_string(tmp[i]) != data1)
                    foundRows.push_back(i);
                else if (op == "between" and between<string>(to_string(tmp[i]), data1, data2))
                    foundRows.push_back(i);
            }
        } else if (elementsTypes[col_i] == "float") {
            vector<float> tmp = (*static_cast<Column<float> *>(cols[col_i])).values;
            for (int i = 0; i < tmp.size(); i++) {
                if (op == "=" and tmp[i] == stof(data1))
                    foundRows.push_back(i);
                else if (op == ">" and tmp[i] > stof(data1))
                    foundRows.push_back(i);
                else if (op == "<" and tmp[i] < stof(data1))
                    foundRows.push_back(i);
                else if (op == ">=" and tmp[i] >= stof(data1))
                    foundRows.push_back(i);
                else if (op == "<=" and tmp[i] <= stof(data1))
                    foundRows.push_back(i);
                else if (op == "<>" and tmp[i] != stof(data1))
                    foundRows.push_back(i);
                else if (op == "between" and between<float>(tmp[i], stof(data1), stof(data2)))
                    foundRows.push_back(i);
            }
        } else if (elementsTypes[col_i] == "char") {
            vector<char> tmp = (*static_cast<Column<char> *>(cols[col_i])).values;
            for (int i = 0; i < tmp.size(); i++) {
                if (op == "=" and tmp[i] == data1[1])
                    foundRows.push_back(i);
                else if (op == ">" and tmp[i] > data1[1])
                    foundRows.push_back(i);
                else if (op == "<" and tmp[i] < data1[1])
                    foundRows.push_back(i);
                else if (op == ">=" and tmp[i] >= data1[1])
                    foundRows.push_back(i);
                else if (op == "<=" and tmp[i] <= data1[1])
                    foundRows.push_back(i);
                else if (op == "<>" and tmp[i] != data1[1])
                    foundRows.push_back(i);
                else if (op == "between" and between<char>(tmp[i], data1[1], data2[1]))
                    foundRows.push_back(i);
            }
        } else if (elementsTypes[col_i] == "string" or elementsTypes[col_i] == "text") {
            vector<string> tmp = (*static_cast<Column<string> *>(cols[col_i])).values;
            /**data1.resize(data1.size()-1);
            reverse(data1.begin(),data1.end());
            data1.resize(data1.size()-1);
            reverse(data1.begin(),data1.end());

            data2.resize(data2.size()-1);
            reverse(data2.begin(),data2.end());
            data2.resize(data2.size()-1);
            reverse(data2.begin(),data2.end());*/

            for (int i = 0; i < tmp.size(); i++) {
                if (op == "=" and tmp[i] == data1)
                    foundRows.push_back(i);
                else if (op == ">" and tmp[i] > data1)
                    foundRows.push_back(i);
                else if (op == "<" and tmp[i] < data1)
                    foundRows.push_back(i);
                else if (op == ">=" and tmp[i] >= data1)
                    foundRows.push_back(i);
                else if (op == "<=" and tmp[i] <= data1)
                    foundRows.push_back(i);
                else if (op == "<>" and tmp[i] != data1)
                    foundRows.push_back(i);
                else if (op == "between" and between<string>(tmp[i], data1, data2))
                    foundRows.push_back(i);
            }
        } else if (elementsTypes[col_i] == "date") {
            vector<Date> tmp = (*static_cast<Column<Date> *>(cols[col_i])).values;
            Date tmp_date1, tmp_date2;
            tmp_date1.set_Date(data1);
            tmp_date2.set_Date(data2);
            for (int i = 0; i < tmp.size(); i++) {
                if (op == "=" and tmp[i] == tmp_date1)
                    foundRows.push_back(i);
                else if (op == ">" and tmp[i] > tmp_date1)
                    foundRows.push_back(i);
                else if (op == "<" and tmp[i] < tmp_date1)
                    foundRows.push_back(i);
                else if (op == ">=" and tmp[i] >= tmp_date1)
                    foundRows.push_back(i);
                else if (op == "<=" and tmp[i] <= tmp_date1)
                    foundRows.push_back(i);
                else if (op == "<>" and !(tmp[i] == tmp_date1))
                    foundRows.push_back(i);
                else if (op == "between" and between<Date>(tmp[i], tmp_date1, tmp_date2))
                    foundRows.push_back(i);
            }
        } else if (elementsTypes[col_i] == "time") {
            vector<Time> tmp = (*static_cast<Column<Time> *>(cols[col_i])).values;
            Time tmp_time1, tmp_time2;
            tmp_time1.set_time(data1);
            tmp_time2.set_time(data2);
            for (int i = 0; i < tmp.size(); i++) {
                if (op == "=" and tmp[i] == tmp_time1)
                    foundRows.push_back(i);
                else if (op == ">" and tmp[i] > tmp_time1)
                    foundRows.push_back(i);
                else if (op == "<" and tmp[i] < tmp_time1)
                    foundRows.push_back(i);
                else if (op == ">=" and tmp[i] >= tmp_time1)
                    foundRows.push_back(i);
                else if (op == "<=" and tmp[i] <= tmp_time1)
                    foundRows.push_back(i);
                else if (op == "<>" and !(tmp[i] == tmp_time1))
                    foundRows.push_back(i);
                else if (op == "between" and between<Time>(tmp[i], tmp_time1, tmp_time2))
                    foundRows.push_back(i);
            }
        }
    } else{
        cerr<<endl<<"Search data isn't of the right type (it should be of type "<<type<<")";
    }

    if(foundRows.empty()){
        noErr=false;
        cerr<<endl<<"No row containing \""<<data1<<"\"";
        if(data2!="/err") cerr<<" or \""<<data2<<"\" were";
        else cerr<<" was";
        cerr<<" found";
    }

    return noErr;
}

void Table::deleteRows(const vector<int> & Rows){
    rows-=Rows.size();
    for (int j=0; j<elementsTypes.size(); j++) {
        if(elementsTypes[j]=="int"){
            Column<int> & vec=(*static_cast<Column<int>*>(cols[j]));
            deleteElements_from_vec(vec.values, Rows);
            deleteElements_from_vec(vec.valuesNullity, Rows);
        }
        if(elementsTypes[j]=="float"){
            Column<float> & vec=(*static_cast<Column<float>*>(cols[j]));
            deleteElements_from_vec(vec.values, Rows);
            deleteElements_from_vec(vec.valuesNullity, Rows);
        }
        if(elementsTypes[j]=="char"){
            Column<char> & vec=(*static_cast<Column<char>*>(cols[j]));
            deleteElements_from_vec(vec.values, Rows);
            deleteElements_from_vec(vec.valuesNullity, Rows);
        }
        if(elementsTypes[j]=="string" or elementsTypes[j]=="text"){
            Column<string> & vec=(*static_cast<Column<string>*>(cols[j]));
            deleteElements_from_vec(vec.values, Rows);
            deleteElements_from_vec(vec.valuesNullity, Rows);
        }
        if(elementsTypes[j]=="date"){
            Column<Date> & vec=(*static_cast<Column<Date>*>(cols[j]));
            deleteElements_from_vec(vec.values, Rows);
            deleteElements_from_vec(vec.valuesNullity, Rows);
        }
        if(elementsTypes[j]=="time"){
            Column<Time> & vec=(*static_cast<Column<Time>*>(cols[j]));
            deleteElements_from_vec(vec.values, Rows);
            deleteElements_from_vec(vec.valuesNullity, Rows);
        }
    }
}

void Table::clear_col(const int &i){ /*https://stackoverflow.com/questions/33805741/delete-pointer-and-object*/
    if(elementsTypes[i]=="int"){
        delete((static_cast<Column<int>*>(cols[i])));
    }
    if(elementsTypes[i]=="float"){
        delete((static_cast<Column<float>*>(cols[i])));
    }
    if(elementsTypes[i]=="char"){
        delete((static_cast<Column<char>*>(cols[i])));
    }
    if(elementsTypes[i]=="string" or elementsTypes[i]=="text"){
        delete((static_cast<Column<string>*>(cols[i])));
    }
    if(elementsTypes[i]=="date"){
        delete((static_cast<Column<Date>*>(cols[i])));
    }
    if(elementsTypes[i]=="time"){
        delete((static_cast<Column<Time>*>(cols[i])));
    }
}

void Table::empty_content(){
    for(int i=0; i<elementsTypes.size(); i++){
        if(elementsTypes[i]=="int"){
            Column<int> & tmp=(*static_cast<Column<int>*>(cols[i]));
            tmp.values.clear();
            tmp.valuesNullity.clear();
        }
        if(elementsTypes[i]=="float"){
            Column<float> & tmp=(*static_cast<Column<float>*>(cols[i]));
            tmp.values.clear();
            tmp.valuesNullity.clear();
        }
        if(elementsTypes[i]=="char"){
            Column<char> & tmp=(*static_cast<Column<char>*>(cols[i]));
            tmp.values.clear();
            tmp.valuesNullity.clear();
        }
        if(elementsTypes[i]=="string" or elementsTypes[i]=="text"){
            Column<string> & tmp=(*static_cast<Column<string>*>(cols[i]));
            tmp.values.clear();
            tmp.valuesNullity.clear();
        }
        if(elementsTypes[i]=="time"){
            Column<Time> & tmp=(*static_cast<Column<Time>*>(cols[i]));
            tmp.values.clear();
            tmp.valuesNullity.clear();
        }
        if(elementsTypes[i]=="date"){
            Column<Date> & tmp=(*static_cast<Column<Date>*>(cols[i]));
            tmp.values.clear();
            tmp.valuesNullity.clear();
        }
    }
    rows=0;
}

bool Table::get_rows_by_data(const int & col_i, const string & searchData, vector<int> & foundRows){
    bool noErr=true;
    const string & type=elementsTypes[col_i];
    noErr=check_data_consistence(searchData, type);

    if(noErr){
        if(type=="int"){
            vector<int> & colVal=(*static_cast<Column<int>*>(cols[col_i])).values;

        }
    } else{
        cerr<<endl<<"Search data isn't of the right type (it should be of type "<<type<<")";
    }
    return noErr;
}

bool Table::set_UPDATE_data(const vector<string> &data, const vector<int> &foundRows) {
    int noErr=true;
    for(int i=0; i<data.size() and noErr; i++){
        string tmp=data[i];
        string col= substr_CC(tmp, 0, 1, ' ', '=');

        int col_i;
        noErr=((col_i=find_col_by_name(col))!=-1);
        if(noErr){
            string & type=elementsTypes[col_i];
            tmp-=(col+"=");
            noErr=check_data_consistence(tmp, type);
            if(noErr){
                if (type=="int") {
                    vector<int> & values = (*static_cast<Column<int> *>(cols[col_i])).values;
                    for (const auto & row: foundRows) {
                        values[row] = stoi(tmp);
                    }
                }
                if (type=="float") {
                    vector<float> & values = (*static_cast<Column<float> *>(cols[col_i])).values;
                    for (const auto & row: foundRows) {
                        values[row] = stof(tmp);
                    }
                }
                if (type=="char") {
                    vector<char> &values = (*static_cast<Column<char> *>(cols[col_i])).values;
                    for (const auto & row: foundRows) {
                        values[row] = stoi(tmp);
                    }
                }
                if (type=="string" or type=="text") {
                    vector<string> & values = (*static_cast<Column<string> *>(cols[col_i])).values;
                    for (const auto & row: foundRows) {
                        values[row] = tmp;
                    }
                }
                if (type=="date") {
                    vector<Date> & values = (*static_cast<Column<Date> *>(cols[col_i])).values;
                    for (const auto & row: foundRows) {
                        Date tmpDate(tmp);
                        values[row] = tmpDate;
                    }
                }
                if (type == "time") {
                    vector<Time> &values = (*static_cast<Column<Time> *>(cols[col_i])).values;
                    for (const auto & row: foundRows) {
                        Time tmpTime(tmp);
                        values[row] = tmpTime;
                    }
                }
            } else{
                cerr << endl << "Inserted data isn't of the correct type! (" << type << " was expected)";
            }
        } else{
            cerr<<endl<<"No column "<<col<<"was found!";
        }
    }
    return noErr;
}

void Table::col_orderer(int colIndex, vector <int> & rowsIndexes, int order){
    string &type = elementsTypes[colIndex];
    vector <int> tmp;
    if (type == "int") {
        vector<int> &values = (*static_cast<Column<int> *>(cols[colIndex])).values;
        tmp = order_vector_indexes<int>(values, order);
    }
    if (type == "float") {
        vector<float> &values = (*static_cast<Column<float> *>(cols[colIndex])).values;
        tmp = order_vector_indexes<float>(values, order);
    }
    if (type == "char") {
        vector<char> &values = (*static_cast<Column<char> *>(cols[colIndex])).values;
        tmp = order_vector_indexes<char>(values, order);
    }
    if (type=="string" or type=="text") {
        vector<string> &values = (*static_cast<Column<string> *>(cols[colIndex])).values;
        tmp = order_vector_indexes<string>(values, order);
    }
    if (type=="date") {
        vector<Date> & values = (*static_cast<Column<Date> *>(cols[colIndex])).values;
        tmp = order_vector_indexes<Date>(values, order);
    }
    if (type=="time") {
        vector<Time> & values = (*static_cast<Column<Time> *>(cols[colIndex])).values;
        tmp = order_vector_indexes<Time>(values, order);
    }
    rowsIndexes = tmp - ( tmp - rowsIndexes);
}

void Table::printCols(vector <string> colSelection, const vector <string> & search, const string &colToOrder, const int &order ){
    bool noErr;
    int index;
    string tmp;
    vector <int> rowsOrder;
    for(int k=0; k<rows; k++) rowsOrder.push_back(k);


    if(colSelection[0]=="*"){
        colSelection=elementsNames;
    }

    if(search[0]!="/err" and search[1] != "0" and search[2]!="/err"){
        rowsOrder.erase(rowsOrder.begin(), rowsOrder.end());
        if(search[1]=="between") tmp=search[3];
        else tmp="/err";
        find_Rows_by_value(search[2],find_col_by_name(search[0]),rowsOrder, search[1], tmp);
    }

    if(order and colToOrder!="/err"){
        col_orderer(find_col_by_name(colToOrder), rowsOrder, order);
    }

    rowsOrder.insert(rowsOrder.begin(), -1);

    for(int j: rowsOrder) {
        for (auto & colSelectedName : colSelection) {
            noErr = ((index = find_col_by_name(colSelectedName)) != -1);
            if (noErr) {
                if(j==-1) {cout<<colSelectedName<<((elementsTypes[index]=="string" or elementsTypes[index]=="text")?"\t\t":"\t");}
                else {
                    string &type = elementsTypes[index];
                    if (type == "int") {
                        vector<int> &values = (*static_cast<Column<int> *>(cols[index])).values;
                        cout << values[j] << "\t";
                    }
                    if (type=="float") {
                        vector<float> & values = (*static_cast<Column<float> *>(cols[index])).values;
                        cout << values[j] << "\t";
                    }
                    if (type=="char") {
                        vector<char> &values = (*static_cast<Column<char> *>(cols[index])).values;
                        cout << values[j] << "\t";
                    }
                    if (type=="string" or type=="text") {
                        vector<string> &values = (*static_cast<Column<string> *>(cols[index])).values;
                        cout << values[j] << (values[j].size()>=8?"\t":"\t\t");
                    }
                    if (type=="date") {
                        vector<Date> & values = (*static_cast<Column<Date> *>(cols[index])).values;
                        cout << values[j].get_day()<<"/";
                        cout << values[j].get_month()<<"/";
                        cout << values[j].get_year()<<"\t";
                    }
                    if (type == "time") {
                        vector<Time> &values = (*static_cast<Column<Time> *>(cols[index])).values;
                        cout << values[j].get_hours()<<":";
                        cout << values[j].get_minutes()<<":";
                        cout << values[j].get_seconds()<<"\t";
                    }
                }
            } else {
                cerr << endl << "No column " << colSelectedName << " was found!";
            }
        }
        cout<<endl;
    }
}

bool Table::printTable_to_file(ofstream & out) {
    bool noErr=true;
    out<<name<<" ";
    out<<rows<<" ";
    out<<primaryKey_index;
    out<<endl;

    for(const int & FTable_i : ForeignTables){
        out<<FTable_i<<" ";
    }
    out<<endl;

    for(const int & FCols_i : ForeignCols){
        out<<FCols_i<<" ";
    }
    out<<endl;

    for(const int & ConCols_i : ConnectedCols){
        out<<ConCols_i<<" ";
    }
    out<<endl;

    for(const string & eltype : elementsTypes){
        out<<eltype<<" ";
    }
    out<<endl;

    for(const string & elname : elementsNames){
        out<<elname<<" ";
    }
    out<<endl<<endl;

    for(int i=0; i<elementsTypes.size(); i++){
        if(elementsTypes[i]=="int"){
            Column<int> & col=(*static_cast<Column<int>*>(cols[i]));
            out<<col.key<<" ";
            out<<col.not_null<<" ";
            out<<col.auto_increment<<endl;
            for(const int & value: col.values){
                out<<to_string(value)<<" ";
            }
            out<<endl;

            for(bool nullity: col.valuesNullity){
                out<<nullity<<" ";
            }
            out<<endl;
            out<<"-"<<endl;
        }
        if(elementsTypes[i]=="float"){
            Column<float> & col=(*static_cast<Column<float>*>(cols[i]));
            out<<col.key<<" ";
            out<<col.not_null<<" ";
            out<<col.auto_increment<<endl;
            for(const float & value: col.values){
                out<<to_string(value)<<" ";
            }
            out<<endl;

            for(bool nullity: col.valuesNullity){
                out<<nullity<<" ";
            }
            out<<endl;
            out<<"-"<<endl;
        }
        if(elementsTypes[i]=="char"){
            Column<char> & col=(*static_cast<Column<char>*>(cols[i]));
            out<<col.key<<" ";
            out<<col.not_null<<" ";
            out<<col.auto_increment<<endl;
            for(const char & value: col.values){
                out<<to_string(value)<<" ";
            }
            out<<endl;

            for(bool nullity: col.valuesNullity){
                out<<nullity<<" ";
            }
            out<<endl;
            out<<"-"<<endl;
        }
        if(elementsTypes[i]=="string" or elementsTypes[i]=="text"){
            Column<string> & col=(*static_cast<Column<string>*>(cols[i]));
            out<<col.key<<" ";
            out<<col.not_null<<" ";
            out<<col.auto_increment<<endl;
            for(string value: col.values){
                if(value.empty()){ value="\"/empty\"";}
                out<<value<<" ";
            }
            out<<endl;

            for(bool nullity: col.valuesNullity){
                out<<nullity<<" ";
            }
            out<<endl;
            out<<"-"<<endl;
        }
        if(elementsTypes[i]=="time"){
            Column<Time> & col=(*static_cast<Column<Time>*>(cols[i]));
            out<<col.key<<" ";
            out<<col.not_null<<" ";
            out<<col.auto_increment<<endl;
            for(const Time & value: col.values){
                string time_str=value.to_string();
                if(time_str.empty()){ time_str="\"/empty\""; }
                out<<time_str<<" ";
            }
            out<<endl;

            for(bool nullity: col.valuesNullity){
                out<<nullity<<" ";
            }
            out<<endl;
            out<<"-"<<endl;
        }
        if(elementsTypes[i]=="date"){
            Column<Date> & col=(*static_cast<Column<Date>*>(cols[i]));
            out<<col.key<<" ";
            out<<col.not_null<<" ";
            out<<col.auto_increment<<endl;
            for(const Date & value: col.values){
                string date_str=value.Date_to_string();
                if(date_str.empty()){ date_str="\"/empty\""; }
                out << date_str << " ";
            }
            out<<endl;

            for(bool nullity: col.valuesNullity){
                out<<nullity<<" ";
            }
            out<<endl;
            out<<"-"<<endl;
        }

    }
    return noErr;
}

void Table::createTable_from_file(ifstream &in, string line) {
    stringstream stream(line);
    stream>>(this->name)>>(this->rows)>>(this->primaryKey_index);

    vector<string> tmp_data;

    getline(in, line);
    line>>(tmp_data);
    for(const string & el : tmp_data){ this->ForeignTables.push_back(stoi(el)); }

    getline(in, line);
    line>>(tmp_data);
    for(const string & el : tmp_data){ this->ForeignCols.push_back(stoi(el)); }

    getline(in, line);
    line>>(tmp_data);
    for(const string & el : tmp_data){ this->ConnectedCols.push_back(stoi(el)); }

    getline(in, line);
    line>>(this->elementsTypes);

    getline(in, line);
    line>>(this->elementsNames);
    getline(in, line);

    for(int i=0; i<elementsTypes.size(); i++){
        createCol_from_file(in, elementsTypes[i], i);
    }
}

void Table::createCol_from_file(ifstream &in, const string &type, int col_i) {
    string key;
    bool not_null, auto_increment;

    string line;
    getline(in, line);
    stringstream stream(line);
    stream>>key>>not_null>>auto_increment;

    string input=key+" "+type;
    if(not_null){
        input+=" not null";
    }
    if(auto_increment){
        input+=" auto_increment";
    }
    create_col(input, true);

    getline(in, line);
    if(type=="int"){
        Column<int> & tmp=(*static_cast<Column<int>*>(cols[col_i]));
        vector<string> tmp_data;
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.values.push_back(stoi(str)); }
        }
        getline(in, line);
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.valuesNullity.push_back(stoi(str)); }
        }
    }
    if(type=="float"){
        Column<float> & tmp=(*static_cast<Column<float>*>(cols[col_i]));
        vector<string> tmp_data;
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.values.push_back(stof(str)); }
        }
        getline(in, line);
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.valuesNullity.push_back(stoi(str)); }
        }
    }
    if(type=="char"){
        Column<char> & tmp=(*static_cast<Column<char>*>(cols[col_i]));
        vector<string> tmp_data;
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.values.push_back(str[0]); }
        }
        getline(in, line);
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.valuesNullity.push_back(stoi(str)); }
        }
    }
    if(type=="string" or type=="text"){
        Column<string> & tmp=(*static_cast<Column<string>*>(cols[col_i]));
        string data=line, element;
        while((element= substr_CC(data, 1, 2, '\"', '\"')) != "/err"){
            tmp.values.push_back(element);
            data-="\""+element+"\" ";
        }
        getline(in, line);
        vector<string> tmp_data;
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.valuesNullity.push_back(stoi(str)); }
        }
    }
    if(type=="date"){
        Column<Date> & tmp=(*static_cast<Column<Date>*>(cols[col_i]));
        vector<string> tmp_data;
        line>>tmp_data;
        if(!tmp_data.empty()) {
            vector<Date> tmp_dates;
            for (int i = 0; i < tmp_data.size(); i++) {
                tmp_dates.resize(i + 1);
                tmp_dates[i].set_Date(tmp_data[i]);
            }
            tmp.values = tmp_dates;
        }
        getline(in, line);
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.valuesNullity.push_back(stoi(str)); }
        }
    }
    if(type=="time"){
        Column<Time> & tmp=(*static_cast<Column<Time>*>(cols[col_i]));
        vector<string> tmp_data;
        line>>tmp_data;
        if(!tmp_data.empty()) {
            vector<Time> tmp_times;
            for (int i = 0; i < tmp_data.size(); i++) {
                tmp_times.resize(i + 1);
                tmp_times[i].set_time(tmp_data[i]);
            }
            tmp.values = tmp_times;
        }
        getline(in, line);
        line>>tmp_data;
        if(!tmp_data.empty()) {
            for (const string &str: tmp_data) { tmp.valuesNullity.push_back(stoi(str)); }
        }
    }
    getline(in, line);
}
