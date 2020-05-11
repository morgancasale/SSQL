//
// Created by carlt on 08/05/20.
//

#include "Table.h"

void Table::get_data(string in){
    if(in.compare(0,3,"int")){
        rows[0].ints.resize(sizeof(list_int)+1);
        //list_<take substring from 0st space to 1st>.resize(sizeof(list_<take substring from 0st space to 1st>)+1);
        rows[0].ints[0].key = in.substr(3,sizeof(in)-3);
        //list_<take substring from 0st space to 1st>.end()=<take substring from 1st space to 2nd>;
        elements.resize(sizeof(elements)+1);
        elements.push_back(in.substr(3,sizeof(in)-3));
    }
    //...
}
void Table::empty_unused_elements() {
    if(rows[0].ints.empty()){   vector<list_int>().swap(rows[0].ints);  }
    if(rows[0].floats.empty()){   vector<list_float>().swap(rows[0].floats);  }
    if(rows[0].chars.empty()){   vector<list_char>().swap(rows[0].chars);  }
    if(rows[0].texts.empty()){   vector<list_string>().swap(rows[0].texts);  }
    if(rows[0].dates.empty()){   vector<list_date>().swap(rows[0].dates);  }
    if(rows[0].times.empty()){   vector<list_time>().swap(rows[0].times);  }
}

Table(string in){
/*name=<take name from in>;
for(int i=0, in[i]!='}', i+=2){
    get_data(<take substring from in from (0st+i) space after '{' to (2nd+i) space>);
*/}
//empty_unused_elements();
}