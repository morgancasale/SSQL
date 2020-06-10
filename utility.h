#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Classes/Date/Date.h"


string tolower(string &in, int stop=-1){ //converts all upper letters of a string to lower ones
    stop = ((stop<0)? in.size()-1 : stop); //if stop<0 takes all the string
    for(int i=0; i<=stop; i++){
        in[i]=tolower(in[i]);
    }
    return in;
}
// it return the substring from the n(counter1) instance of char1
// to the n(counter2) instance of char2
// tricks: counter1=0 to take from beginning ignoring char1
//         and counter2=-1 to take up to the end ignoring char2
string substr_from_c_to_c(const string &in, const int &counter1, const int &counter2, const char &char1= ' ', const char &char2=' ') {
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

bool clean_input(string &in, const vector<string> & programKeyWords){
    string tmp=in;
    tolower(tmp);
    for(string a: programKeyWords) {
        if (tmp.find(a)!=tmp.npos) in.replace(tmp.find(a),a.size(), a);
    }
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

string operator -(string minuend, const string & subtrahend){
    return erase_substr(minuend, subtrahend);
}

void operator -=(string & minuend, const string & subtrahend){
    erase_substr(minuend, subtrahend);
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
    int num=0, i=0, k=0;

    if(!isalpha(in[0]) and !isalpha(in[in.size()])){
        i++;
        k++;
    }

    for(; i<in.size()-k; i++){
        for(; isalpha(in[i]); i++){
        }
        if(in[i]!=0 and isalpha(in[i-1])){
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

bool is_a_Time(const string & var){
    bool response=true;

    int hours, min, sec;

    char sub;
    if(var.find(':')!=-1){
        sub=':';
    }
    else if(var.find('.')!=-1){
        sub='.';
    }else{
        response=false;
    }
    if(response){
        stringstream ss=data_ss(var, sub);
        ss>>hours>>min>>sec;
        if(hours<0 or hours>24){ //checks hours
            response=false;
        }
        if(min<0 or min>60){ //checks minutes
            response=false;
        }
        if(sec<0 or sec>60){
            response=false;
        }
    }

    return response;
}
bool is_a_Date(const string & var){
    bool response=true;

    int day, month, year;

    char sub;
    bool err=false;
    if(var.find(':')!=-1){
        sub=':';
    } else if(var.find('.')!=-1){
        sub='.';
    } else if(var.find('/')!=-1){
        sub='/';
    } else{
        response=false;
    }

    if(response){
        stringstream ss=data_ss(var, sub);
        ss>>day>>month>>year;

        if(month<0 or month>12){
            response=false;
        }
        if(response) {
            switch (month) {
                default:
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (day < 0 or day > 31) {
                        response = false;
                    }
                    break;
                case 2:
                    if (day < 0 or day > 28 + (1 - abs(year) % 4)) { //this account also for leap years
                        response = false;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if (day < 0 or day > 30) {
                        response = false;
                    }
                    break;
            }
        }
    }
    return response;
}

bool check_data_consistence(const string & var, const string & to_check){
    bool response=false;

    if(substr_from_c_to_c(var, 1, 2, '"', '"')!="/err"){
        response = (to_check == "string" or to_check =="text");
    } else
    if(substr_from_c_to_c(var, 1, 2, 39, 39)!="/err"){ //char a=39 --> a='
        response = (to_check == "char");
    } else
    if(var.find('.')!=-1){
        bool Date_resp;
        if(is_a_Time(var) and !(Date_resp=is_a_Date(var))){ response = (to_check=="time"); }
        else if(Date_resp){ response = (to_check=="date"); }
        else{ response = (to_check=="float"); }
    } else
    if(var.find(':')!=-1){
        bool Date_resp;
        if(is_a_Time(var) and !(Date_resp=is_a_Date(var))){ response = (to_check=="time"); }
        else if(Date_resp){ response = (to_check=="date"); }
    } else
    if(var.find('/')!=-1){ response = (to_check=="date"); }
    else{
        response = (to_check=="int");
    }

    return response;
}

template<typename type> vector<type> operator -(vector<type> minuend, const vector<type> & subtrahend){

    for(int i=0; i<subtrahend.size(); i++){
        string sub=subtrahend[i];//prendo un sottraendo
        bool found=false;
        for(int j=0; j<minuend.size() and !found; j++){
            string min=minuend[j]; //prendo il minuendo
            if(min==sub){
                for(int k=j; k<minuend.size()-1; k++){
                    minuend[k]=minuend[k+1];
                }
                minuend.resize(minuend.size()-1);
                found=true;
            }
        }
    }
    return minuend;
}


#endif