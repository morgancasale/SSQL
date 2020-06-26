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
        "delete",
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

const string reserved_words[2]{
    "/delete",
    "/err"
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
        "references",
        "between"
};

vector <string> possibleOperators={
        "=",
        "<",
        ">",
        "<=",
        ">=",
        "<>",
        "between"
};

string take_command(string & in){
    bool err=true; string tmp;

    int start_i=0;
    while(!isalpha(in[start_i])){ start_i++; }
    in=in.substr(start_i,in.size());

    vector <string> dictionary;
    dictionary.insert(dictionary.end(), allowed_types.begin(), allowed_types.end());
    dictionary.insert(dictionary.end(), allowed_coms.begin(), allowed_coms.end());
    dictionary.insert(dictionary.end(), keyWords.begin(), keyWords.end());

    clean_input(in, dictionary);
    for(const string & s:allowed_coms) {
        if(in.find(s) != in.npos) {
            err=false;
            in-=(s+" ");
            return s;
        }
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
    if(in.find("primary key(")==-1 and in.find("primary key (")==-1){
        primaryKeyErr=true;
    }
    if(!err and !primaryKeyErr) {
        string line, foreignKeys;
        int end2 = in.find(");");
        if (in.find("foreign key") != -1) {
            foreignKeys = substr_from_s_to_s(in, "foreign key", ");", false, true);
            in -= ", " + foreignKeys;
        }
        bool flag = true;
        if (end2 != in.npos and !err) {//this checks if there is the final substring ");" somewhere
            for (int i = 0; i < end2 and !err and
                            flag; i++) { //this checks if every input starts with a space end ends with a ',', it considers input of two and three letters
                line = substrcc(in, 2, 1, ' ', ',');
                if (num_of_words(line) > 5) {
                    err = true;
                }
                if (line == "/err" and !err) {
                    line = substrcc(in, 2, 2, ' ', ')');
                    string tmp_str=substrcc(line, 0, 1, ' ', '(');
                    if (num_of_words(tmp_str) > 2) {
                        err = true;
                    }
                    in -= line;
                    string tmp = substrcc(in, 1, 1, '(', ';');
                    replace_chars(tmp, {' '}, -1);

                    flag = (tmp != ")");
                } else {
                    erase_substr(in, line + ", ");
                }
            }
            while (!err and !foreignKeys.empty()) {
                bool noErr = true;
                line = substrcc(foreignKeys, 0, 1, ' ', ',');
                while (!foreignKeys.empty()) {
                    line += ",";
                    if (line == "/err,") {
                        line = substrcc(foreignKeys, 0, -1);
                    }
                    noErr = (line.find("foreign key") != -1 and line.find("references") != -1);
                    if (noErr) {
                        noErr = (num_of_chars(line, '(') == 2 and num_of_chars(line, ')') == 2);
                        if (noErr) {
                            string tmp_str = substrcc(line, 1, 1, '(', ')');
                            noErr = (num_of_words(tmp_str) == 1);
                            if (noErr) {
                                tmp_str = substrcc(line, 2, 2, '(', ')');
                                noErr = (num_of_words(tmp_str) == 1);
                                if (noErr) {
                                    string ref = substrcc(line, 1, -1, ')', ' ');
                                    tmp_str = substrcc(ref, 0, 1, ' ', '(');
                                    noErr = (num_of_words(tmp_str) == 2);
                                    if (noErr) {
                                        tmp_str = substrcc(ref, 1, 1, '(', ')');
                                        noErr = (num_of_words(tmp_str) == 1);
                                    }
                                }
                            }
                        }
                    }
                    foreignKeys -= line;
                    line = substrcc(foreignKeys, 0, 1, ' ', ',');
                }
                err = !noErr;
            }
        } else {
            err = true;
        }

        if (in.find(");") == -1 and !err) {
            err = true;
        }
    }
    if(primaryKeyErr){
        cerr<<endl<<"No primary key specified!";
    }else if(err){
        cerr<<endl<<"CREATE command Syntax error!";
    }

    return (!err and !primaryKeyErr);
}

bool control_CREATE_data(vector<string> in){
    bool noErr=true;
    for(string tmp: in){
        tolower(tmp);
        for(const string & word: allowed_coms){ noErr=(tmp!=word); }
        for(const string & word: allowed_types){ noErr=(tmp!=word); }
        for(const string & word: reserved_words){ noErr=(tmp!=word); }
    }
    return noErr;
}

bool control_drop(const string & in){
    bool noErr=true;
    noErr=(in[in.size()-1]==';');
    if(noErr){ noErr = (num_of_words(in) == 1); }

    if(!noErr){
        cerr<<endl<<"Drop Table command syntax error!";
    }
    return noErr;
};

bool control_truncate(const string & in){ return control_drop(in); };

bool control_insert(string in){
    bool noErr=true;
    int counter=0;

    //controlla se ci sia il termine "values", un ';' alla fine, che ci sia solo una parola
    //tra insert e la parentesi, che ci siano solo 2 '(' e 2 ')' e che l'ultimo carattere sia ')'
    noErr= (in.find("values")!=in.npos and in[in.size()-1]==';');
    noErr&=(num_of_words(substrcc(in, 0, 1, ' ', '(')));
    noErr= noErr and (num_of_chars(in, '(')==2 and num_of_chars(in, ')')==2);
    noErr= noErr and (in[in.size()-2]==')');

    if(noErr){
        string no_content= replace_content(in, '(', ')');
        string tmp_line=in.substr(0, in.find("values"));
        noErr=(num_of_chars(tmp_line, '(')==1 and num_of_chars(tmp_line,')')==1);
        if(noErr) {
            string secondLine = in.substr(no_content.find("values"), in.find(';') - no_content.find("values")+1);
            string firstLine = in - secondLine;
            noErr=(secondLine.find("values")!=-1);

            if(noErr) {
                //controllo prima riga
                if (firstLine.find('(') == in.npos or firstLine.find(')') == in.npos
                    or num_of_words(firstLine.substr(0, firstLine.find('('))) != 1) { noErr = false; }
                else {
                    counter = num_of_words(firstLine.substr(firstLine.find('('), firstLine.find(')')));
                }

                //controllo la seconda riga
                if (secondLine.find('(') == in.npos or secondLine.find(')') == in.npos
                    or num_of_words(secondLine.substr(0, secondLine.find('('))) != 1) { noErr = false; }
                else {
                    //elimino le stringhe per non causare problemi al contatore dopo
                    for (int i = 0; i < character_counter(secondLine, '"'); i++) {
                        string toErase = "\"" + substrcc(secondLine, 1, 2, '"', '"') + "\"";
                        erase_substr(secondLine, toErase);
                    }

                    //elimino i caratteri per non causare problemi al contatore dopo
                    for (int i = 0; i < character_counter(secondLine, 39); i++) {
                        string toErase = substrcc(secondLine, 1, 2, 39, 39);
                        if (toErase.size() != 1) { noErr = false; }
                        else { //controlla se la stringa presa tra le virgolette è di un solo carattere
                            toErase = "'" + toErase + "'";
                            erase_substr(secondLine, toErase);
                        }

                    }

                    //controllo il numero di dati inseriti che corrisponda a counter
                    noErr = (character_counter(secondLine, ',') == (counter - 1));
                }
            }
        }
    }
    if (!noErr) {
        cerr << "INSERT INTO syntax error!";
    }
    return noErr;
}

bool control_delete(string in){
    bool noErr=true;
    if(in[in.size()-1]!=';' or in.find("=")==-1){ noErr=false; }
    if(substrcc(in, 1, 2) != "where"){ noErr =false; }
    if(!noErr){
        cerr<<endl<<"DELETE command syntax error!";
    }
    return noErr;
}

bool control_update(string in){
    bool noErr=(in[in.size()-1]==';');
    if(noErr){
        int tmp;
        noErr=(num_of_words(in.substr(0,tmp=in.find("set")))==1);
        if(noErr){
            in=in.substr(tmp+4, ((tmp+4)-(in.size()-1)));
            noErr=(in.find("where")!=-1);
            if(noErr){
                for(; in.find("where")!=0 and noErr;){
                    string data1= substrcc(in, 0, 1, ' ', '=');
                    noErr=(num_of_words(data1)==1);

                    string data2= substrcc(in, 1, 1, '=', ',');
                    data2+=",";
                    if(data2=="/err,"){
                        data2= substr_from_s_to_s(in, "=", " where");
                    }

                    if(noErr){
                        in-=(data1+"="+data2+" ");
                    }
                }
                if(noErr){
                    in-="where ";
                    string data= substrcc(in, 0, 1, ' ', '=');
                    noErr=(num_of_words(data) == 1);
                }
            }
        }
    }
    if(!noErr){
        cerr<<endl<<"UPDATE command syntax error!";
    }
    return noErr;
}

bool control_select(string in){
    bool noErr=(in[in.size()-1]==';');
    int c=0;
    string s;
    string tmp=" ";
    if(noErr){
        in-=";";
        if(in.find("from")!=in.npos and character_counter((tmp = in.substr(0,in.find("from"))),',') == num_of_words(tmp)-1) {
            in-=tmp;
            if(in.find("where") != in.npos and num_of_words(substr_from_s_to_s(in, "from", "where")) == 1){
                noErr=false;
                for(string oper: possibleOperators){
                    if((tmp = take_the_N_nextWord(in, "where", 2))==oper){
                        noErr=true;
                        if(tmp=="between"){
                            tmp = take_the_N_nextWord(in, "where", 4);
                            if(tmp == "and"){
                                s = substr_from_s_to_s(in, "between", take_the_N_nextWord(in, tmp, 1), false, true);
                                in-= s;
                            } else noErr=false;
                        }
                    }
                }
                if(noErr) {
                    in -= "from" + substr_from_s_to_s(in, "from", "where") + "where";
                    if (num_of_words(in) > 2) {
                        if (in.find("order by") != in.npos) {
                            tmp = in.substr(in.find("order by"), in.size() - in.find("order by"));
                            if ((num_of_words(tmp)) == 4) {
                                tmp = take_the_N_nextWord(tmp, "by", 2);
                                if (tmp != "asc" and tmp != "desc") noErr = false;
                            } else noErr = false;
                        } else noErr = false;
                    } else if (num_of_words(in) < 2) noErr = false;
                }
            }
            else if(num_of_words(in) > 2){
                if(in.find("order by") != in.npos){
                    tmp = in.substr(in.find("order by"),in.size()-in.find("order by"));
                    if(num_of_words(tmp)==4){
                        tmp=take_the_N_nextWord(tmp, "by", 2);
                        if(tmp!="asc" and tmp!="desc") noErr=false;
                    }
                }
                else noErr=false;
            }
            else if(num_of_words(in) < 2) noErr=false;
        }
        else noErr=false;
    }
    if(!noErr){
        cerr<<endl<<"SELECT command syntax error!";
    }
    return noErr;
}
#endif //CS_PROJECT_SYNTAX_H
