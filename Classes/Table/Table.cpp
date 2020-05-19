#include "Table.h"
#include "../../syntax.h"

Table::Table(const string &in){
    if(!check_CREATE_syntax(in)){
        cerr<<endl<<"CREATE command syntax error!";
    } else{
        vector<string> data=get_CREATE_data(in);
        bool err=false;
        for(int i=0; i<data.size() and !err; i++){
            process_CREATE_data(data);
        }
    }
}

void *Table::create_col(const string &in) {
    string key=substr_from_c_to_c(in, 0, 1, ' ', ' ', false);
    string type=substr_from_c_to_c(in, 1, 2);
    elements.push_back(type);
    bool not_null=false;
    if(substr_from_c_to_c(in, 2, -1)=="not null"){
        not_null=true;
    }

    if(type=="int"){
        static Column<int> tmp;
        tmp.key=key;
        tmp.not_null=not_null;
        return static_cast<void *>(&tmp);
    } else
    if(type=="float"){
        static Column<float> tmp;
        tmp.key=key;
        tmp.not_null=not_null;
        return static_cast<void *>(&tmp);
    } else
    if(type=="char"){
        static Column<char> tmp;
        tmp.key=key;
        tmp.not_null=not_null;
        return static_cast<void *>(&tmp);
    } else
    if(type=="string"){
        static Column<string> tmp;
        tmp.key=key;
        tmp.not_null=not_null;
        return static_cast<void *>(&tmp);
    } else
    if(type=="date"){
        static Column<Date> tmp;
        tmp.key=key;
        tmp.not_null=not_null;
        return static_cast<void *>(&tmp);
    } else
    if(type=="time"){
        static Column<Date> tmp;
        tmp.key=key;
        tmp.not_null=not_null;
        return static_cast<void *>(&tmp);
    }
}

void Table::Table2(const string &in) {
    cols.push_back(create_col(in));
}
