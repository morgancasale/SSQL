#include "Table.h"
#include "../../syntax.h"

Table::Table(const string &in){
    if(!check_CREATE_syntax(in)){
        cerr<<endl<<"CREATE command syntax error!";
    } else{
        vector<string> data=get_CREATE_data(in);
        bool err=false;
        for(int i=0; i<data.size() and !err; i++){
            create_col(data[i]);
        }
    }
}

void *Table::create_col(const string &in) {
    bool err=false;

    string key=substr_from_c_to_c(in, 0, 1, ' ', ' ', false);
    string type=substr_from_c_to_c(in, 1, 2);
    if(check_existence(elementsNames, key)){
        cerr<<"Column named "<<key<<" (of type "<<type<<") already exists!";
        return nullptr;
    }
    if(key=="/err" or type=="/err"){
        err=true;
    }
    elementsTypes.push_back(type);
    elementsNames.push_back(key);

    bool notNull=false;
    string tmp;
    if((tmp=substr_from_c_to_c(in, 2, -1))!="/err"){
        if(tmp=="not null"){
            notNull=true;
        } else{
            err=true;
        }
    }

    if(type=="int" and !err){
        static Column<int> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        return static_cast<void *>(&tmp);
    } else
    if(type=="float" and !err){
        static Column<float> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        return static_cast<void *>(&tmp);
    } else
    if(type=="char" and !err){
        static Column<char> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        return static_cast<void *>(&tmp);
    } else
    if(type=="string" and !err){
        static Column<string> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        return static_cast<void *>(&tmp);
    } else
    if(type=="date" and !err){
        static Column<Date> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        return static_cast<void *>(&tmp);
    } else
    if(type=="time" and !err){
        static Column<Date> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        return static_cast<void *>(&tmp);
    } else{
        err=true;
    }

    if(err){
        cerr<<endl<<"CREATE input syntax error!";
    }
}

void Table::Table2(const string &in) {
    cols.push_back(create_col(in));
}
