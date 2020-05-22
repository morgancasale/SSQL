#include "Table.h"
#include "../../utility.h"

Table::Table(const string &in){
    if(!check_CREATE_syntax(in)){
        cerr<<endl<<"CREATE command syntax error!";
    } else{
        vector<string> data=get_CREATE_data(in);
        for(const auto &i : data){
            create_col(i);
        }
    }
}

void *Table::create_col(string in) {
    bool err=false;

    bool auto_increment=false;
    if(in.find("auto_increment")!=-1){
        auto_increment=true;
        erase_substr(in," auto_increment");
    }

    bool notNull=false;
    string tmp;
    if((tmp=substr_from_c_to_c(in, 2, -1))!="/err"){
        if(tmp=="not null"){
            notNull=true;
        } else{
            err=true;
        }
    }
    string key=substr_from_c_to_c(in, 0, 1, ' ', ' ', false);
    string type;
    if(notNull){
        type=substr_from_c_to_c(in, 1, 2);
    } else{
        type=substr_from_c_to_c(in, 1, -1);
    }

    if(type!="int" and auto_increment){
        cerr<<endl<<"Type "<<type<<" doesn't support auto_increment parameter!";
        return nullptr;
    }

    if(check_existence(elementsNames, key) and !err){
        cerr<<"Column named "<<key<<" (of type "<<type<<") already exists!";
        return nullptr;
    }
    if(key=="/err" or type=="/err"){
        err=true;
    }
    elementsTypes.push_back(type);
    elementsNames.push_back(key);

    if(type=="int" and !err){
        static Column<int> tmp;
        tmp.key=key;
        tmp.not_null=notNull;
        tmp.auto_increment=auto_increment;
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
        return nullptr;
    }
}

bool Table::check_CREATE_syntax(string in, const bool &show_err){ //it returns true if no error was found
    bool err=false;

    string first_line=substr_from_c_to_c(in, 0, 4, false);
    if(num_of_words(first_line)!=3){
        err=true;
    }
    if(first_line[first_line.size()-1]!='(' and !err){ //this check if there is a '(' after the table name
        err=true;
    }


    string line;
    int end2=in.find(");");
    if(end2!=-1 and !err){//this checks if there is the final substring ");" somewhere
        for(int i=0; i<end2 and !err and substr_from_c_to_c(in, 1, 1, '(', ')', false)!=" "; i++){ //this checks if every input starts with a space end ends with a ',', it considers input of two and three letters
            line=substr_from_c_to_c(in, 4, 1, ' ', ',', false);
            if(substr_from_c_to_c(in, 5, 6, ' ', ',', false)=="int"){
                if(num_of_words(line)>5){ err=true; }
            } else{
                if (num_of_words(line) > 4) { err = true; }
            }
            if(line=="/err" and !err){
                line=substr_from_c_to_c(in, 4, 1, ' ', ')', false);
                string line2=substr_from_c_to_c(in, 4, 2, ' ', ')', false);
                if(line=="/err" or line2=="/err"){
                    err=true;
                }
                erase_substr(in, line2);
                erase_substr(in, line);
            } else{
                erase_substr(in, line+", ");
            }

        }
    } else{
        err=true;
    }

    if(in.find(");")==-1 and !err){
        err=true;
    }

    if(err and show_err){
        cerr<<endl<<"CREATE command Syntax error!";
    }

    return !err;
}

vector<string> Table::get_CREATE_data(string in){
    vector<string> data;
    data.resize(1);
    string a=substr_from_c_to_c(in, 2, 3, ' ', ' ', false);
    data[0]=a;

    string line;
    for(int i=1; substr_from_c_to_c(in, 1, 1, '(', ')', false)!="  "; i++){//this checks if there is the final substring ");" somewhere
        data.resize(i+1);
        data[i]=substr_from_c_to_c(in, 4, 1, ' ', ',', false);
        if(data[i]=="/err"){
            data[i]=substr_from_c_to_c(in, 4, 7, ' ', ' ', false);
            erase_substr(in, data[i]);
        }else{
            erase_substr(in, data[i]+", ");
        }

    }

    return data;
}

void Table::empty_table() {
    for (int i = 0; i < cols.size(); i++)
        static_cast<Column<typeof(string_to_type(elementsTypes[i]))> *>(cols[i])->values.resize(0);
}
