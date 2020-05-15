#include "Table.h"

void Table::get_data(string in){
    if(in.compare(0,3,"int")){
        defaultrow.ints.resize(sizeof(list_int)+1);
        defaultrow.ints[0].key = in.substr(3,sizeof(in)-3);
        elements.resize(sizeof(elements)+1);
        elements.push_back(in.substr(3,sizeof(in)-3));
    }

    //...
}
void Table::empty_unused_elements() {
    if(defaultrow.ints.empty()){   vector<list_int>().swap(defaultrow.ints);  }
    if(defaultrow.floats.empty()){   vector<list_float>().swap(defaultrow.floats);  }
    if(defaultrow.chars.empty()){   vector<list_char>().swap(defaultrow.chars);  }
    if(defaultrow.texts.empty()){   vector<list_string>().swap(defaultrow.texts);  }
    if(defaultrow.dates.empty()){   vector<list_date>().swap(defaultrow.dates);  }
    if(defaultrow.times.empty()){   vector<list_time>().swap(defaultrow.times);  }
}

Table::Table(string in){
    /*name=<take name from in>;
    for(int i=0, in[i]!='}', i+=2){
        get_data(<take substring from in from (0st+i) space after '{' to (2nd+i) space>);
    }
    empty_unused_elements();*/
}
