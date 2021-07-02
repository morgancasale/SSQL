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
        "between",
        "and"
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
    while(!isalphanum(in[start_i])){ start_i++; }
    in=in.substr(start_i,in.size());

    vector <string> dictionary;
    dictionary.insert(dictionary.end(), allowed_types.begin(), allowed_types.end());
    dictionary.insert(dictionary.end(), allowed_coms.begin(), allowed_coms.end());
    dictionary.insert(dictionary.end(), keyWords.begin(), keyWords.end());

    clean_input(in, dictionary);
    for(const string & s:allowed_coms) {
        if(in.find(s) != -1) {
            err=false;
            in-=(s+" ");
            return s;
        }
    }
    if(err) cout<<RED<<endl<<"Command not recognised!"<<RESET<<endl;
    return "/err";
};

bool control_create(string in){
    bool err = false, primaryKeyErr=false;
    //controllo sintassi prima riga
    if(in[in.size()-1]==-1){ err=true; }
    if(!err and in.find('(')!=-1 and num_of_words(in.substr(0,in.find('(')))!=1) {
        err = true;
    }
    if(!err and in.find("primary key")==-1){
        primaryKeyErr=true;
    }
    if(!err and in.find("not_null")!=-1 ){
        err=true;
    }
    if(!err and !primaryKeyErr) {
        string line, foreignKeys;
        int end2 = in.find(");");
        if (in.find("foreign key") != -1) {
            foreignKeys = substr_SS(in, "foreign key", ");", false, true);
            in -= ", " + foreignKeys;
        }
        bool flag = true;
        if (end2 != -1 and !err) {//this checks if there is the final substring ");" somewhere
            for (int i = 0; i < end2 and !err and
                            flag; i++) { //this checks if every input starts with a space end ends with a ',', it considers input of two and three letters
                line = substr_CC(in, 1, 1, '(', ',');
                if (num_of_words(line) > 5) {
                    err = true;
                }
                if (line == "/err" and !err) {
                    line = substr_CC(in, 1, 1, '(', ';');
                    string tmp_str= substr_CC(line, 0, 1, ' ', '(');
                    if (num_of_words(tmp_str) > 3) {
                        err = true;
                    }
                    in -= line;
                    string tmp = substr_CC(in, 1, 1, '(', ';');
                    replace_chars(tmp, {' '}, -1);

                    flag = (!tmp.empty());
                } else {
                    erase_substr(in, line + ", ");
                }
            }
            while (!err and !foreignKeys.empty()) {
                bool noErr = true;
                line = substr_CC(foreignKeys, 0, 1, ' ', ',');
                while (!foreignKeys.empty()) {
                    line += ",";
                    if (line == "/err,") {
                        line = substr_CC(foreignKeys, 0, -1);
                    }
                    noErr = (line.find("foreign key") != -1 and line.find("references") != -1);
                    if (noErr) {
                        noErr = (character_counter(line, '(') == 2 and character_counter(line, ')') == 2);
                        if (noErr) {
                            string tmp_str = substr_CC(line, 1, 1, '(', ')');
                            noErr = (num_of_words(tmp_str) == 1);
                            if (noErr) {
                                tmp_str = substr_CC(line, 2, 2, '(', ')');
                                noErr = (num_of_words(tmp_str) == 1);
                                if (noErr) {
                                    string ref = substr_CC(line, 1, -1, ')', ' ');
                                    tmp_str = substr_CC(ref, 0, 1, ' ', '(');
                                    noErr = (num_of_words(tmp_str) == 2);
                                    if (noErr) {
                                        tmp_str = substr_CC(ref, 1, 1, '(', ')');
                                        noErr = (num_of_words(tmp_str) == 1);
                                    }
                                }
                            }
                        }
                    }
                    foreignKeys -= line;
                    line = substr_CC(foreignKeys, 0, 1, ' ', ',');
                }
                err = !noErr;
            }
        } else {
            err = true;
        }
    }
    if(primaryKeyErr){
        cout<<RED<<endl<<"No primary key specified!"<<RESET<<endl;
    }else if(err){
        cout<<RED<<endl<<"CREATE command Syntax error!"<<RESET<<endl;
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
        cout<<RED<<endl<<"Drop Table command syntax error!"<<RESET<<endl;
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
    noErr&=(num_of_words(substr_CC(in, 0, 1, ' ', '(')));
    noErr= noErr and (character_counter(in, '(')==2 and character_counter(in, ')')==2);
    noErr= noErr and (in[in.size()-2]==')');
    noErr= noErr and (character_counter(in,'\"')%2==0);
    if(noErr) remove_content(in, '\"', '\"', noErr);


    if(noErr){
        string no_content= replace_content(in, '(', ')');
        string tmp_line=in.substr(0, in.find("values"));
        noErr=(character_counter(tmp_line, '(')==1 and character_counter(tmp_line,')')==1);
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
                        string toErase = "\"" + substr_CC(secondLine, 1, 2, '"', '"') + "\"";
                        erase_substr(secondLine, toErase);
                    }

                    //elimino i caratteri per non causare problemi al contatore dopo
                    for (int i = 0; i < character_counter(secondLine, 39); i++) {
                        string toErase = substr_CC(secondLine, 1, 2, 39, 39);
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
        cout<<RED<<"INSERT INTO syntax error!"<<RESET<<endl;
    }
    return noErr;
}

bool control_delete(string in){
    string tmp, s;
    bool noErr=true;
    if(in[in.size()-1]!=';'){ noErr=false; }
    if(take_the_N_nextWords(in, "", 1) != "where"){ noErr =false; }
    if (noErr){
        noErr=false;
        for(string oper: possibleOperators){
            if((tmp = take_the_N_nextWords(in, "where", 2)) == oper){
                noErr=true;
                if(tmp=="between") {
                    if (in.find("and") != -1) {
                        if (num_of_words(substr_SS(in, "between", "and")) == 0 or num_of_words(substr_SS(in, "and", ";")) == 0)
                            noErr = false;
                    } else noErr = false;
                }
            }
        }
    }
    if(!noErr){
        cout<<RED<<endl<<"DELETE command syntax error!"<<RESET<<endl;
    }
    return noErr;
}

bool control_update(string in){
    bool noErr=(in[in.size()-1]==';'), exit=false;
    if(noErr) remove_content(in, '\"', '\"', noErr);
    if(noErr){
        unsigned int tmp, tmp2;
        string setRow;
        if(in.find("set")!=-1)  noErr=(num_of_words(in.substr(0,tmp=in.find("set")))==1);
        else noErr=false;
        if(noErr){
            in-=in.substr(0,in.find(take_the_N_nextWords(in, "", 2)));
            if(in.find("where")!=-1)   {
                setRow = substr_SS(in, "", "where",false,true);
                in-=setRow;
            }
            else noErr=false;
            if(noErr){
                tmp=character_counter(setRow, '=');
                tmp2=character_counter(setRow, ',');
                if(tmp-1 == tmp2){
                    setRow += ',';
                    char c='=';
                    while(!exit and setRow!=","){
                        string data1 = substr_CC(setRow, 0, 1, ' ', c);
                        exit=!(noErr=(num_of_words(data1)==1));
                        if(character_counter(data1, '"')==2){ exit=!(noErr=true); }
                        setRow-=data1;
                        c = (c=='=') ? ',' : '=';
                    }
                }
                else noErr=false;

                if(noErr){
                    exit=false;
                    for(string oper: possibleOperators){
                        if(take_the_N_nextWords(in, "where", 2) == oper){
                            exit=true;
                            if(num_of_words(substr_SS(in,"where",oper))!=1) noErr=false;
                            else if(oper=="between"){
                                if(in.find("and")!=-1){
                                    if(num_of_words(substr_SS(in,"between","and"))==0 or num_of_words(substr_SS(in,"and",";"))==0) noErr=false;
                                } else noErr=false;
                            }
                        }
                    }
                    if(!exit) noErr=false;
                }
            }
        }
    }
    if(!noErr){
        cout<<RED<<endl<<"UPDATE command syntax error!"<<RESET<<endl;
    }
    return noErr;
}

bool control_select(string in){
    bool noErr=(in[in.size()-1]==';');
    string tmp=" ";
    unsigned int c=0, a=character_counter((tmp = in.substr(0,in.find("from"))),',');
    string s;

    if(noErr){
        if(in.find("from")!=-1 and  a==num_of_words(tmp)-1 or tmp.find('*')!=-1) {
            in-=tmp;
            if(in.find("where") != -1 and num_of_words(substr_SS(in, "from", "where")) == 1){
                bool exit=false;
                for(const string & oper: possibleOperators){
                    if(take_the_N_nextWords(in, "where", 2) == oper){
                        exit=true;
                        if(num_of_words(substr_SS(in,"where",oper))!=1) noErr=false;
                        else if(oper=="between"){
                            if(in.find("and")!=-1){
                                if(num_of_words(s=substr_SS(in,"and",";"))==0 or num_of_words(substr_SS(in,"between","and"))==0) noErr=false;
                            } else noErr=false;
                        }
                    }
                }
                if(!exit) noErr=false;

                if(noErr) {
                    in -= "from" + substr_SS(in, "from", "where") + "where";
                    if (num_of_words(in) > 2) {
                        if (in.find("order by") != -1) {
                            tmp = in.substr(in.find("order by"), in.size() - in.find("order by"));
                            if ((num_of_words(tmp)) == 4) {
                                tmp = take_the_N_nextWords(tmp, "by", 2);
                                if (tmp != "asc" and tmp != "desc") noErr = false;
                            } else noErr = false;
                        }
                    } else if (num_of_words(in) < 2) noErr = false;
                }
            }
            else if(num_of_words(in) > 2){
                if(in.find("order by") != -1){
                    tmp = in.substr(in.find("order by"),in.size()-in.find("order by"));
                    if(num_of_words(tmp)==4){
                        tmp= take_the_N_nextWords(tmp, "by", 2);
                        if(tmp!="asc" and tmp!="desc") noErr=false;
                    } else noErr=false;
                } else noErr=false;
            } else if(num_of_words(in) < 2) noErr=false;
        } else noErr=false;
    }
    if(!noErr){
        cout<<RED<<endl<<"SELECT command syntax error!"<<RESET<<endl;
    }
    return noErr;
}

#endif //CS_PROJECT_SYNTAX_H