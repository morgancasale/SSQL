#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Classes/Database/Database.h"

stringstream data_ss(string in, const char &sub){ //remove char sub from string then returns a stringstream from the modified input string
    replace(in.begin(), in.end(), sub, ' ');
    stringstream ss(in);
    return ss;
}


string tolower(string &in){ //converts all upper letters of a string to lower ones
    for(int i=0; i<in.size(); i++){
        in[i]=tolower(in[i]);
    }
    return in;
}

string substr_from_c_to_c(string in, const int &c1, const int &c2, const char &c= ' ') { //it return the sub string from the space s1 to the space s2, enter 0 to take from beginning and -1 to take up to the end
    int start=0, end=-1;
    int chars=0, i=0;
    bool found=false;
    for(; i<in.size() and chars != c2; i++){
        if(in[i]==c){
            chars++;
        }
        if(chars==c1 and !found){
            start=i+1;
            found=true;
        }
    }
    end=i-1;
    if(c1==0){
        start=0;
    }
    if(c2==-1){
        end=in.size();
    }
    return in.substr(start,end-start);
}