#include "Table.h"
#include "../../syntax.h"
void Table::get_data(string in){
    if(in.compare(0,3,"int")){
        defaultRow.ints.resize(sizeof(list_int)+1);
        defaultRow.ints[0].key = in.substr(3,sizeof(in)-3);
        elements.resize(sizeof(elements)+1);
        elements.push_back(in.substr(3,sizeof(in)-3));
    }

    //...
}
void Table::empty_unused_elements() {
    if(defaultRow.ints.empty()){   vector<list_int>().swap(defaultRow.ints);  }
    if(defaultRow.floats.empty()){   vector<list_float>().swap(defaultRow.floats);  }
    if(defaultRow.chars.empty()){   vector<list_char>().swap(defaultRow.chars);  }
    if(defaultRow.texts.empty()){   vector<list_string>().swap(defaultRow.texts);  }
    if(defaultRow.dates.empty()){   vector<list_date>().swap(defaultRow.dates);  }
    if(defaultRow.times.empty()){   vector<list_time>().swap(defaultRow.times);  }
}

Table::Table(string in){
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
