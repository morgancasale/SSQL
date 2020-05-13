#ifndef CS_PROJECT_METACLASS_H
#define CS_PROJECT_METACLASS_H


/*
class list_<type>{
    string key;
    <type> val;
}
class element (or column){
    string title;
    bool can_be_null=true;
    bool auto_increment=false;
}

class Row{
    string key;
    vector<list_int> ints;
    vector<list_float> floats;
    vector<list_char> chars;
    vector<list_string> texts;
    vector<list_date> dates;
    vector<list_time> times;
}


class Table {
    string name;
    vector<element> elements;
    vector<Row> rows;
    void get_data(string in){
        list_<take substring from 0st space to 1st>.resize(sizeof(list_<take substring from 0st space to 1st>)+1);
        list_<take substring from 0st space to 1st>.end()=<take substring from 1st space to 2nd>;
        elements.resize(sizeof(elements=+1));
        elements.end()=<take substring from 1st space to 2nd>;
        if(<there is a 3rd space>){
            if(<take substring from 2nd space to the 3rd>=="NOT"){
                elements.end().can_be_null=true;
                if(<there is a 4th space>){
                    if(<take substring from 4th space to ','>=="AUTO_INCREMENT"){
                        elements.end().auto_increment=true;
                }
            }else if(<take substring from 2nd space to the 3rd>=="AUTO_INCREMENT"){
                elements.end().auto_increment=true;
                if(<there is a 4th space>){
                    if(<take substring from 4th space to the 5th>=="NOT"){
                        elements.end().can_be_null=true;
                    }
                }
            }
        }
    }
    void empty_unused_elements(){
        if(ints=={}){
            vector<list_int>().swap(ints);
        }
        if(floats=={}){
            vector<list_float> floats;
        }
        ...
    }

    Table(string in){
        name=<take name from in>;
        for(int i=0, in[i]!='}', i+=2){
            get_data(<take substring from in from (0st+i) space after '{' to (2nd+i) space>);
        }
        empty_unused_elements();
    }
    ~Table(
};

*/
#endif //CS_PROJECT_METACLASS_H
