//
// Created by tabas on 21/05/2020.
//

#ifndef CS_PROJECT_SYNTAX_H
#define CS_PROJECT_SYNTAX_H
#include "utility.h"

const vector <string> allowed_coms={
        "create table",
        "drop table",
        "truncate table",
        "insert into",
        "delete from",
        "update",
        "select",
        "quit()"
};

const vector <string> allowed_types={
        "int",
        "float",
        "char",
        "string",
        "text",
        "date",
        "time"
};

const vector <string> keyWords={
        "not null",
        "auto_increment",
        "primary key",
        "values",
        "where",
        "set",
        "from",
        "order by",
        "desc",
        "asc",
        "foreign key",
        "references"
};

string take_command(string & in){
    bool err=false; string tmp;

    vector <string> dictionary;
    dictionary.insert(dictionary.end(), allowed_types.begin(), allowed_types.end());
    dictionary.insert(dictionary.end(), allowed_coms.begin(), allowed_coms.end());
    dictionary.insert(dictionary.end(), keyWords.begin(), keyWords.end());

    clean_input(in, dictionary);
    for(const string & s:allowed_coms) {
        if(in.find(s) != in.npos) {
            err=false;
            tmp=in.substr(in.find(s), s.size());
            in-=(tmp+" ");
            return tmp;
        }else   err=true;
    }
    if(err) cerr<<endl<<"Comando non riconosciuto!"<<endl;
    return "/err";
};

bool control_create(string in){
    bool err = false, primaryKeyErr=false;
    //controllo sintassi prima riga
    if(in.find('(')!=in.npos and num_of_words(in.substr(0,in.find('(')))!=1) {
        err = true;
    }
    if(in.find("primary key(")==-1){
        primaryKeyErr=true;
    }

    string line;
    int end2=in.find(");");
    bool tmp=true;
    if(end2!=in.npos and !err){//this checks if there is the final substring ");" somewhere
        for(int i=0; i<end2 and !err and tmp; i++){ //this checks if every input starts with a space end ends with a ',', it considers input of two and three letters
            line=substr_from_c_to_c(in, 2, 1, ' ', ',');
            if(num_of_words(line)>5){
                err=true;
            }
            if(line=="/err" and !err){
                line=substr_from_c_to_c(in, 2, 1, ' ', ';');
                line.resize(line.size()-2);
                if(num_of_words(line)>5){
                    err=true;
                }
                erase_substr(in, line);
                tmp=substr_from_c_to_c(in, 1, 1, '(', ';')!="  )";
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

    if(primaryKeyErr){
        cerr<<endl<<"No primary key specified!";
    }else if(err){
        cerr<<endl<<"CREATE command Syntax error!";
    }

    return (!err and !primaryKeyErr);
};
bool control_drop(const string & in){return num_of_words(in)==1;};
bool control_truncate(const string & in){return num_of_words(in)==1;};
bool control_insert(string in){
    bool noErr=true;
    int counter=0;

    //controlla se ci sia il termine "values" e un ';' alla fine
    if(in.find("values")==in.npos or in.find(';')==in.npos) noErr=false;

    string secondLine = in.substr(in.find("values"), in.find(';'));
    string firstLine = in-secondLine;

    //controllo prima riga
    if(firstLine.find('(')==in.npos or firstLine.find(')')==in.npos
        or num_of_words(firstLine.substr(0, firstLine.find('(')))!=1) noErr=false;
    else {
        counter = num_of_words(firstLine.substr(firstLine.find('('), firstLine.find(')')));
    }

    //controllo la seconda riga
    if(secondLine.find('(')==in.npos or secondLine.find(')')==in.npos
       or num_of_words(secondLine.substr(0, secondLine.find('(')))!=1) { noErr=false; }
    else {
        //elimino le stringhe per non causare problemi al contatore dopo
        for(int i=0; i<character_counter(secondLine,'"'); i++) {
            string toErase="\""+substr_from_c_to_c(secondLine, 1, 2, '"', '"')+"\"";
            erase_substr(secondLine, toErase);
        }

        //elimino i caratteri per non causare problemi al contatore dopo
        for(int i=0; i<character_counter(secondLine,39); i++) {
            string toErase=substr_from_c_to_c(secondLine, 1, 2, 39, 39);
            if(toErase.size()!=1){ noErr=false; } else{ //controlla se la stringa presa tra le virgolette è di un solo carattere
                toErase="'"+toErase+"'";
                erase_substr(secondLine, toErase);
            }

        }

        //controllo il numero di dati inseriti che corrisponda a counter
        noErr= (character_counter(secondLine, ',') == (counter-1));
    }

    if(!noErr){
        cerr<<"INSERT INTO syntax error!";
    }

    return noErr;
}

bool control_delete(string in){
    bool noErr=true;
    if(in[in.size()]!=';' or in.find("=")==-1){ noErr=false; }
    if(substr_from_c_to_c(in, 3, 4)!="where"){ noErr =false; }
    if(!noErr){
        cerr<<endl<<"DELETE command syntax error!";
    }
    return noErr;
}

#endif //CS_PROJECT_SYNTAX_H
