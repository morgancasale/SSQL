//
// Created by tabas on 21/05/2020.
//

#ifndef CS_PROJECT_SYNTAX_H
#define CS_PROJECT_SYNTAX_H
#include "utility.h"

string allowed_coms[8]={
        "create table",
        "drop table",
        "truncate table",
        "insert into",
        "delete from",
        "update",
        "select",
        "quit()"
};

string take_command(string & in){
    bool err=false; string tmp;
    clean_input(in);
    for(string s:allowed_coms) {
        if(in.find(s) != in.npos) {
            err=false;
            tmp=in.substr(in.find(s), s.size());
            in.erase(in.find(s),s.size());
            return tmp;
        }else   err=true;
    }
    if(err) cerr<<endl<<"Comando non riconosciuto!"<<endl;
    return "/err";
};



bool control_create(const string & in){};
bool control_drop(const string & in){return num_of_words(in)==1;};
bool control_truncate(const string & in){return num_of_words(in)==1;};



#endif //CS_PROJECT_SYNTAX_H
