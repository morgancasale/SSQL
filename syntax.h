#ifndef CS_PROJECT_SYNTAX_H
#define CS_PROJECT_SYNTAX_H

#include <iostream>
#include "utility.h"
using namespace std;

bool check_CREATE_syntax(string in, const bool &show_err=true){ //it returns true if no error was found
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

    if(err and show_err){
        cerr<<endl<<"CREATE command Syntax error!";
    }

    return !err;
}

vector<string> get_CREATE_data(string in){
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

#endif //CS_PROJECT_SYNTAX_H
