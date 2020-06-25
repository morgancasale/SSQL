#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Classes/Date/Date.h"


string tolower(string &in, int stop= -1){ //converts all upper letters of a string to lower ones
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
string substrcc(const string &in, const int &counter1, const int &counter2, const char &char1= ' ', const char &char2= ' ') {
    int start=0, end=1;
    int tmpCounter1=0, i=0, tmpCounter2=0;
    bool found1=false, found2=false;
    if(counter1==0 and counter2==-1){
        start=0;
        end=in.size();
        found1=true;
        found2=true;
    } else{
        for (; i < in.size() and tmpCounter2 != counter2; i++) {
            if (in[i] == char1) {
                tmpCounter1++;
            }
            if (in[i] == char2) {
                tmpCounter2++;
            }
            if (tmpCounter1 == counter1 and !found1) {
                start = i + 1;
                found1 = true;
            }
        }
    }

    if(in[i-1] == char2){
        found2=true;
    }

    end=i-1;
    if(counter1 == 0){
        start=0;
        found1=true;
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
        int first_c=in.find(tmp); //finds the position of the first occurrence of the character tmp
        if(first_c != -1){//find returns -1 if the characters isn't found
            int found=0;
            for(int i= first_c + 1; i < in.size(); i++){ //Loops over all characters of the input starting from first_c
                if((in[i]!=in[first_c]) or (in[i] != tmp)){
                    first_c++;
                    in[first_c]=in[i];
                } else{
                    found++;
                }
            }
            in.resize(in.size()-found);
        } else{
          err=true;
        }
    }

    if(err and show_err){
        cerr<<"Can't find one or more of the characters to delete!"<<endl;
    }
    return err;
}

string replace_chars(string &in, const vector<char> sub, const char &car) {
    for(const char & c: sub){
        int pos=in.find(c);
        while(pos!=-1){
            string tmp="";
            if(car!=-1){
                tmp[0]=car;
            }
            in.replace(pos,1, tmp);
            pos=in.find(c);
        }
    }

    return in;
}


bool clean_input(string & in, const vector<string> & programKeyWords){
    string tmp=in;
    tolower(tmp);
    for(const string & a: programKeyWords) {
        if (tmp.find(a)!=tmp.npos){
            string big=in.substr(tmp.find(a), a.size());
            while(big!=a and in.find(big)!=-1){
                in.replace(in.find(big), a.size(), a);
            }
        }
    }
    replace_chars(in, {'\n', '\t', '\r'}, ' ');
    return remove_duplicate_chars(in, {' '}, false);
}

string get_command_from_file(string in, const int &comm_i){
    return in;
}

string erase_substr(string &in, string to_erase){
    int pos=in.find(to_erase);
    if(pos!=-1){
        in.erase(pos, to_erase.size());
        replace_chars(in, {'\n'}, ' ');
    }
    return in;
}

string operator -(string minuend, const string & subtrahend){
    return erase_substr(minuend, subtrahend);
}

void operator -=(string & minuend, const string & subtrahend){
    erase_substr(minuend, subtrahend);
}
string substr_from_s_to_s(string in, string s1, string s2, const bool & reverse=false, bool fromZero=false){
    int start, end;
    int shift=1;
    if(fromZero){ shift=0; }

    if(reverse){
        std::reverse(in.begin(), in.end());
        std::reverse(s1.begin(), s1.end());
        std::reverse(s2.begin(), s2.end());
        start = in.find(s2) + shift;
        end = in.find(s1);
    } else{
        start = in.find(s1) + shift;
        end = in.find(s2);
    }

    string out=in.substr(start, end - start);;
    if(start==-1 or end==-1){
        return "/err";
    }
    else{
        if(reverse){ std::reverse(out.begin(), out.end()); }
        return out;
    }
}

int num_of_words(string in){
    int num=0, i=0, k=0, end=in.size()-1;

    for(; !isalpha(in[end]); end--){}
    end++;
    in=in.substr(0, end);
    in.push_back(' ');

    if(!isalpha(in[0]) and !isalpha(in[in.size()-1])){
        i++;
        k++;
    }

    for(; i<in.size()-k; i++){
        for(; isalpha(in[i]); i++){}
        if(i!=0 and isalpha(in[i-1])){
            num++;
        }
    }
    if(num==0 and isalpha(in[in.size()-1])){ num++; }

    char characters[2]={'_', '-'};
    while(in.find('_')!=-1 or in.find('-')!=-1){
        for(const char & ch: characters){
            int pos=in.find(ch);
            if(pos!=-1 and isalpha(in[pos-1]) and isalpha(in[pos+1])){
                num--;
                in[pos]=' ';
            }
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

    int hours=-1, min=-1, sec=-1;

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

    int day=-1, month=-1, year=-1;

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
        if(day<=0 or day>31) response=false;
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

//The first parameter is the input data while the second one is the type to check
bool check_data_consistence(const string & var, const string & type){
    bool noErr=false;

    if(substrcc(var, 1, 2, '"', '"') != "/err"){
        noErr = (type == "string" or type == "text");
    } else
    if(substrcc(var, 1, 2, 39, 39) != "/err"){ //char a=39 --> a='
        noErr = (type == "char");
    } else
    if(var.find('.')!=-1){
        bool Date_resp;
        bool Time_resp;
        if(Time_resp=is_a_Time(var) and !(Date_resp=is_a_Date(var))){
            noErr = (type == "time");
            Time_resp=is_a_Time(var);
        }
        else if(Date_resp){
            noErr = (type == "date"); }
        else{
            noErr = (type == "float"); }
    } else
    if(var.find(':')!=-1){
        bool Date_resp;
        if(is_a_Time(var) and !(Date_resp=is_a_Date(var))){ noErr = (type == "time"); }
        else if(Date_resp){ noErr = (type == "date"); }
    } else
    if(var.find('/')!=-1){ noErr = (type == "date"); }
    else{
        noErr = (type == "int");
    }

    return noErr;
}

template<typename type> vector<type> operator -(vector<type> minuend, const vector<type> & subtrahend){

    for(int i=0; i<subtrahend.size(); i++){
        type sub=subtrahend[i];//prendo un sottraendo
        bool found=false;
        for(int j=0; j<minuend.size() and !found; j++){
            type min=minuend[j]; //prendo il minuendo
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

template<typename type> void operator -=(vector<type> & minuend, const vector<type> & subtrahend){
    for(int i=0; i<subtrahend.size(); i++){
        type sub=subtrahend[i];//prendo un sottraendo
        bool found=false;
        for(int j=0; j<minuend.size() and !found; j++){
            type min=minuend[j]; //prendo il minuendo
            if(min==sub){
                for(int k=j; k<minuend.size()-1; k++){
                    minuend[k]=minuend[k+1];
                }
                minuend.resize(minuend.size()-1);
                found=true;
            }
        }
    }
}

template<typename type> void deleteElements_from_vec(vector<type> & minuend, const vector<int> & rows){
    for(int i=0; i<rows.size(); i++){
        for(int k=rows[i]; k<minuend.size()-1; k++){
            minuend[k]=minuend[k+1];
        }
        minuend.resize(minuend.size()-1);
    }
}

string take_the_next_word(const string & in, string before){
    string tmp, after;
    stringstream iss(in);
    if(in.find(before)==in.npos){
        cerr<<endl<<"La parola non esiste nella frase";
        return "/err";
    }
    while(iss>>tmp){
        if(tmp==before){
            iss>>after;
        }
        after-=";";
    }
    return after;
}


int num_of_chars(const string & in, const char & c){
    int num=0;
    for(const char tmp: in){
        if(tmp==c){ num++; }
    }
    return num;
}

string replace_content(string in, const char & start, const char & end, const char & sub=' '){
    int start_i=0, end_i=0;
    while(start_i<num_of_chars(in,start) and end_i<num_of_chars(in,end)){
        string repl=" ";
        string tmp= substrcc(in, start_i + 1, end_i + 1, start, end);
        int s=tmp.size();
        for(int j=0; j<s-1; j++){ repl.push_back(' '); }
        in.replace(in.find(tmp), tmp.size(), repl);
        start_i++;
        end_i++;
    }
    return in;
}

void operator>>(const string & str, vector<string> & vec){
    vec.resize(0);
    stringstream ss(str);
    string tmp;
    ss>>tmp;
    while(!tmp.empty()){
        vec.push_back(tmp);
        tmp="";
        ss>>tmp;
    }
}

string removeSpaces_fromStart_andEnd(string & in){
    int start=0, end=in.size()-1;
    for(; in[start]==' '; start++){}
    for(; in[end]==' '; end--){}
    in=in.substr(start, end-start+1);

    return in;
}

#endif