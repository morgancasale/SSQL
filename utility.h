#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Classes/Date/Date.h"

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
// it return the substring from the n(counter1) instance of char1
// to the n(counter2) instance of char2
// tricks: counter1=0 to take from beginning ignoring char1
//         and counter2=-1 to take up to the end ignoring char2
string substr_from_c_to_c(const string &in, const int &counter1, const int &counter2, const char &char1= ' ', const char &char2=' ', const bool &show_error=true) {
    int start=0, end=1;
    int tmpCounter1=0, i=0, tmpCounter2=0;
    bool found1=false, found2=false;
    for(; i<in.size() and tmpCounter2 != counter2; i++){
        if(in[i] == char1){
            tmpCounter1++;
        }
        if(in[i] == char2){
            tmpCounter2++;
        }
        if(tmpCounter1 == counter1 and !found1){
            start=i+1;
            found1=true;
        }
    }

    if(in[i-1] == char2){
        found2=true;
    }

    end=i-1;
    if(counter1 == 0){
        start=0;
    }
    if(counter2 == -1){
        end=in.size();
        found2=true;
    }

    if(!found1 or !found2 and show_error) {
        cerr << endl << "One or the two characters weren't found!";
    }
    if(!found1 or !found2){ //if one or two characters aren't found then the function returns "/err"
        return "/err"; //Maybe we should add an exception for the use of "/err" as any name
    } else{
        return in.substr(start,end-start);
    }
}

int character_counter(const string & in, char char_to_count){
    int counter=0;
    for(char c:in){
        if(c==char_to_count) counter++;
    }
    return counter;
}

bool remove_duplicate_chars(string & in, vector<char> c, const bool & show_err=true){
    bool err=false;

    for(const char & tmp: c){
        int last_c=in.find(tmp); //finds the position of the first occurrence of the character tmp
        if(last_c != -1){ //find returns -1 if the characters isn't found
            for(int i= last_c + 1; i < in.size(); i++){ //Loops over all characters of the input starting from last_c
                if((in[i]!=in[last_c]) or (in[i]!=tmp)){
                    last_c++;
                    in[last_c]=in[i];
                }
            }
            in[++last_c]='\0';
        } else{
          err=true;
        }
    }

    if(err and show_err){
        cerr<<"Can't find one or more of the characters to delete!"<<endl;
    }
    return err;
}

string remove_endl(string &in){
    int pos=in.find('\n');
    while(pos!=-1){
        in.replace(pos,1, " ");
        pos=in.find('\n');
    }
    return in;
}

bool clean_input(string &in){
    tolower(in);
    remove_endl(in);
    return remove_duplicate_chars(in, {' '});
}

string get_command_from_file(string in, const int &comm_i){
    return in;
}

string erase_substr(string &in, const string &to_erase){
    int pos=in.find(to_erase);
    if(pos!=-1){
        in.erase(pos, to_erase.size());
        remove_endl(in);
    }
    return in;
}

string get_substr_from_s_to_s(const string &in, const string &s1, const string &s2){
    int start=in.find(s1);
    int end=in.find(s2)+s2.size();

    if(start==-1 or end==-1){
        return "/err";
    }
    else{
        return in.substr(start, end - start);
    }
}

int num_of_words(const string &in){
    int num=0;
    for(int i=0; i<in.size(); i++){
        for(; isalpha(in[i]); i++){
        }
        if(isalpha(in[i-1])){
            num++;
        }
    }
    return num;
}

template<typename type> bool check_existence(const vector<type> &vec, const type &el){
    bool found=false;
    for(const type &x : vec){
        if(x==el){ found=true; }
    }
    return found;
}

template <typename T=int>
T string_to_type(const string& in, bool show_err=false){
    T a;
    if(in=="int") { int b; a=b; }
    else if(in=="float")  { float b; a=b; }
    else if(in=="char") { char b;a=b; }
    else if(in=="string" or in=="text")  {string b; a=b;}
    else if(in=="date") { Date b;a=b; }
    else if(in=="time") { Time b; a=b; }
    else if(show_err) { cerr<<endl<<"Type "<<in<<" not supported"<<endl; void* b;  a=b; }
    return a;
};

bool check_data_consistence(const string & var, const string & to_check){
    bool response=false;
    if(substr_from_c_to_c(var, 1, 2, '"', '"', false)!="/err"){
        response = (to_check == "string");
    } else
    if(substr_from_c_to_c(var, 1, 2, 39, 39, false)!="/err"){ //char a=39 --> a='
        response = (to_check == "char");
    } else
    if(var.find(".")!=-1){
        bool Date_resp;
        if(is_a_Time(var) and !(Date_resp=is_a_Date(var))){
            response = (to_check=="time");
        }else
        if(Date_resp){
            response = (to_check=="date");
        }else{
            response = (to_check=="float");
        }
    } else
    if(var.find(":")!=-1){
        bool Date_resp;
        if(is_a_Time(var) and !(Date_resp=is_a_Date(var))){
            response = (to_check=="time");
        }else
        if(Date_resp){
            response = (to_check=="date");
        }
    } else{
        response = (to_check=="int");
    }
    return response;
}

#endif