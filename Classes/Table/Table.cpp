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
            noErr=!create_col(data[i]);
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
        key=substr_from_c_to_c(in, 1, 1, '(', ')', false);

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

bool Table::create_col(string in) {
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

    string key=substr_from_c_to_c(in, 0, 1, ' ', ' ', false);
    err=!check_key(key);

    string type=" ";
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
        static vector<Column<int>> tmp;
        Column<int> tmp2;
        tmp2.key=key;
        tmp2.not_null=notNull;
        tmp2.auto_increment=auto_increment;
        tmp.push_back(tmp2);
        cols.push_back(static_cast<void *>(&tmp[tmp.size()-1]));
    } else
    if(!err and type == "float"){
        static vector<Column<float>> tmp;
        Column<float> tmp2;
        tmp2.key=key;
        tmp2.not_null=notNull;
        tmp.push_back(tmp2);
        cols.push_back(static_cast<void *>(&tmp[tmp.size()-1]));
    } else
    if(!err and type == "char"){
        static vector<Column<char>> tmp;
        Column<char> tmp2;
        tmp2.key=key;
        tmp2.not_null=notNull;
        tmp.push_back(tmp2);
        cols.push_back(static_cast<void *>(&tmp[tmp.size()-1]));
    } else
    if(!err and (type == "string" or type == "text")){
        static vector<Column<string>> tmp;
        Column<string> tmp2;
        tmp2.key=key;
        tmp2.not_null=notNull;
        tmp.push_back(tmp2);
        cols.push_back(static_cast<void *>(&tmp[tmp.size()-1]));
    } else
    if(!err and type == "date") {
        static vector<Column<Date>> tmp;
        Column<Date> tmp2;
        tmp2.key=key;
        tmp2.not_null=notNull;
        tmp.push_back(tmp2);
        cols.push_back(static_cast<void *>(&tmp[tmp.size()-1]));
    } else
    if(!err and type == "time"){
        static vector<Column<Time>> tmp;
        Column<Time> tmp2;
        tmp2.key=key;
        tmp2.not_null=notNull;
        tmp.push_back(tmp2);
        cols.push_back(static_cast<void *>(&tmp[tmp.size()-1]));
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
    for(int i=1; substr_from_c_to_c(in, 1, 1, '(', ')', false)!="  "; i++){//this checks if there is the final substring ");" somewhere
        data.resize(i+1);
        data[i]=substr_from_c_to_c(in, 2, 1, ' ', ',', false);
        if(data[i]=="/err"){
            data[i]=substr_from_c_to_c(in, 2, 7, ' ', ';', false);
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
