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

bool control_create(string in){
    bool err = false;
    //controllo sintassi prima riga
    if(in.find('(')!=in.npos and num_of_words(in.substr(0,in.find('(')))==1) {
            err = true;
    }

    string line;
    int end2=in.find(");");
    if(end2!=in.npos and !err){//this checks if there is the final substring ");" somewhere
        for(int i=0; i<end2 and !err and substr_from_c_to_c(in, 1, 1, '(', ')', false)!=" "; i++){ //this checks if every input starts with a space end ends with a ',', it considers input of two and three letters
            line=substr_from_c_to_c(in, 4, 1, ' ', ',', false);
            if(num_of_words(line)>4){
                err=true;
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

    if(err){
        cerr<<endl<<"CREATE command Syntax error!";
    }

    return !err;
};
bool control_drop(const string & in){return num_of_words(in)==1;};
bool control_truncate(const string & in){return num_of_words(in)==1;};
bool control_insert(string in){
    bool err=false;
    int counter=0;
    if(in.find("values")==in.npos or in.find(';')==in.npos) return false;
    string secondLine = in.substr(in.find("values"), in.find(';'));
    string firstLine = erase_substr(in, secondLine);
    //controllo prima riga
    if(firstLine.find('(')==in.npos or firstLine.find(')')==in.npos
        or num_of_words(firstLine.substr(0, firstLine.find('(')))!=1) return false;
    else {
        counter = num_of_words(firstLine.substr(firstLine.find('('), firstLine.find(')')));
    }
    //controllo la seconda riga
    if(secondLine.find('(')==in.npos or secondLine.find(')')==in.npos
       or num_of_words(secondLine.substr(0, secondLine.find('(')))!=1) return false;
    else {
        //Fare controllo n parole=counter
    }
    return err;
}
/*
INSERT INTO CUSTOMERS (AGE, ADDRESS, NAME)
VALUES (20, “via Roma 10, Torino”, “Francesco Rossi”);
*/
#endif //CS_PROJECT_SYNTAX_H
