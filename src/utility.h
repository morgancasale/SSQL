#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H
#define RED     "\033[31m"
#define RESET   "\033[0m"
using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include "Classes/Date/Date.h"


string tolower(string & in, int stop= -1){ //converts all upper letters of a string to lower ones
    stop = ((stop<0)? (int)in.size()-1 : stop); //if stop<0 takes all the string
    for(int i=0; i<=stop; i++){
        in[i]=tolower(in[i]);
    }
    return in;
}

// it return the substring from the n(counter1) instance of char1
// to the n(counter2) instance of char2
// tricks: counter1=0 to take from beginning ignoring char1
//         and counter2=-1 to take up to the end ignoring char2
string substr_CC(const string & in, const int & counter1, const int & counter2, const char & char1= ' ', const char & char2= ' ') {
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

unsigned int character_counter(const string & in, char char_to_count){
    int counter=0;
    for(char c:in){
        if(c==char_to_count) counter++;
    }
    return counter;
}

bool remove_duplicate_chars(string & in, const vector<char> & c, const bool & show_err=true){
    bool err=false;

    for(const char & tmp: c){
        int first_c=in.find(tmp); /*finds the position of the first occurrence of the character tmp*/
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
        cout<<RED<<"Can't find one or more of the characters to delete!"<<RESET<<endl;
    }
    return err;
}

string replace_chars(string & in, const vector<char> & sub, const char & c) {
    for(const char & i: sub){
        int pos=in.find(i);
        while(pos!=-1){
            string tmp="";
            if(i != -1){
                tmp[0]=c;
            }
            in.replace(pos,1, tmp);
            pos=in.find(i);
        }
    }

    return in;
}

unsigned long int find_nIterations(string in, const string & search, const int & it){
    int pos=in.find(search);
    for(int i=0; i<it-1 and pos!=-1; i++){
        vector<char>tmp;
        tmp.resize(search.size());
        string repl(tmp.begin(), tmp.end());
        in.replace(pos,search.size(), repl);
        pos=in.find(search);
    }
    return pos;
}

void clean_input(string & in, const vector<string> & programKeyWords){
    string tmp=in;
    tolower(tmp);
    for(const string & a: programKeyWords) {
        unsigned long int pos=0;
        if(tmp.find(a)!=-1) {
            for (int i = 1; (pos = find_nIterations(tmp, a, i)) != -1; i++) {
                unsigned long int val = pos + a.size();
                bool flag = (tmp[val]==' ' or tmp[val]==',' or tmp[val]==')' or tmp[val]=='(' or tmp[val]=='\000' or tmp[val]==';');
                flag &=(pos==0) or (tmp[pos-1]==' ' or tmp[pos-1]==',' or tmp[pos-1]==')' or tmp[pos-1]=='(');

                if (flag) {
                    in.replace(pos, a.size(), a);
                }
            }
        }
    }
    replace_chars(in, {'\n', '\t', '\r'}, ' ');
    remove_duplicate_chars(in, {' '}, false);
}

string erase_substr(string & in, const string & to_erase){
    int pos=in.find(to_erase);
    if(pos!=-1){
        in.erase(pos, to_erase.size());

    }
    return in;
}

string operator -(string minuend, const string & subtrahend){
    return erase_substr(minuend, subtrahend);
}

void operator -=(string & minuend, const string & subtrahend){
    erase_substr(minuend, subtrahend);
}

string substr_SS(string in, string s1, string s2, const bool & reverse= false, bool fromZero= false){
    int start, end;
    if(s1.empty()){ start=0; }
    int shift = s1.size();
    if(fromZero){ shift=0; }

    if(reverse){
        std::reverse(in.begin(), in.end());
        std::reverse(s1.begin(), s1.end());
        std::reverse(s2.begin(), s2.end());
        start = (int)in.find(s2) + shift;
        end = in.find(s1);
    } else{
        start = (int)in.find(s1) + shift;
        end = in.find(s2);
    }

    string out=in.substr(start, end - start);
    if(start==-1 or end==-1){
        return "/err";
    }
    else{
        if(reverse){ std::reverse(out.begin(), out.end()); }
        return out;
    }
}

bool isalphanum(const char & in){ return isalnum(in) or isalpha(in); }

unsigned int num_of_words(string in){
    int num=0, i=0, k=0, start=0, end=(int)in.size()-1;
    int ciao=0;

    for(; !isalphanum(in[start]) and start<=in.size()-1; start++){}
    for(; !isalphanum(in[end]) and end>=0; end--){}
    end++;
    in=in.substr(start, end-start);
    in.push_back(' ');
    if(!in.empty()) {
        if (!isalphanum(in[0]) and !isalphanum(in[in.size() - 1])) {
            i++;
            k++;
        }

        for (; i < in.size() - k; i++) {
            for (; isalphanum(in[i]); i++) {}
            if (i != 0 and isalphanum(in[i - 1])) {
                num++;
            }
        }
        if (num == 0 and isalphanum(in[in.size() - 1])) { num++; }

        char characters[4] = {'_', '-', '.', ':'};
        while (in.find('_') != -1 or in.find('-') != -1 or in.find('.') != -1 or in.find(':') != -1) {
            for (const char &ch: characters) {
                int pos = in.find(ch);
                if (pos != -1) {
                    if (isalphanum(in[pos - 1]) and isalphanum(in[pos + 1]))
                        num--;
                    in[pos] = ' ';
                }
            }
        }
    } else{ num=0; }
    return num;
}

bool is_a_Time(const string & var){
    bool response=true;

    int hours=-1, min=-1, sec=-1;
    unsigned int dots=character_counter(var, '.');
    unsigned int col=character_counter(var, ':');

    char sub;
    if(var.find(':')!=-1 and (col==1 or col==2)){
        sub=':';
    }
    else if(var.find('.')!=-1 and (dots==1 or dots==2)){
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
        if(sec!=-1) {
            if (sec < 0 or sec > 60) {
                response = false;
            }
        }
    }

    return response;
}

bool is_a_Date(const string & var){
    bool response=true;

    int day=-1, month=-1, year=-1;

    char sub;
    bool err=false;
    if(var.find('-')!=-1 and character_counter(var, '-')==2){
        sub='-';
    } else if(var.find('.')!=-1 and character_counter(var, '.')==2){
        sub='.';
    } else if(var.find('/')!=-1 and character_counter(var, '/')==2){
        sub='/';
    } else{
        response=false;
    }

    if(response){
        if(substr_CC(var, 2, -1, sub).size()==4) {
            stringstream ss = data_ss(var, sub);
            ss >> day >> month >> year;
            if (day <= 0 or day > 31) response = false;
            if (month < 0 or month > 12) {
                response = false;
            }
            if (response) {
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
        } else{
            response=false;
        }
    }
    return response;
}

//The first parameter is the input data while the second one is the type to check
bool check_data_consistence(const string & var, const string & type){
    bool noErr=false;

    if(substr_CC(var, 1, 2, '"', '"') != "/err"){
        noErr = (type == "string" or type == "text");
    } else
    if(substr_CC(var, 1, 2, 39, 39) != "/err"){
        noErr = (type == "char");
    } else
    if(var.find('.')!=-1){
        bool Date_resp=is_a_Date(var);
        bool Time_resp=is_a_Time(var);
        if(Time_resp and !Date_resp){
            if (character_counter(var, '.') == 1){
                noErr = (type == "time") or (type == "float");
            } else
                noErr = (type == "time");
        }
        else if(Date_resp){
            noErr = (type == "date"); }
        else{
            noErr = (type == "float"); }
    } else
    if(var.find(':')!=-1){
        bool Date_resp=is_a_Date(var);
        bool tmp=is_a_Time(var);
        if(tmp and !Date_resp){
            noErr = (type == "time");
        }
        else if(Date_resp){ noErr = (type == "date"); }
    } else
    if(var.find('/')!=-1){ noErr = (type == "date"); }
    else if(character_counter(var,'-')==2){ noErr = (type == "date"); }
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

template<typename type> void deleteElements_from_vec(vector<type> & vec, const vector<int> & els){
    int h=0;
    for(int k : els){
        k-=h;
        for(; k < vec.size() - 1; k++){
            vec[k]=vec[k + 1];
        }
        vec.resize(vec.size() - 1);
        h++;
    }
}

string take_the_N_nextWords(const string & in, string before, int N){
    string tmp, after;
    stringstream iss(in);
    if(before.empty()){
        before=substr_CC(in, 0, 1, 0, ' ');
        replace_chars(before, {' '}, -1);
    } if(in.find(before)==-1){
        cout<<RED<<endl<<"La parola non esiste nella frase"<<RESET;
        return "/err";
    }

    if(N<=0 or N>in.size()){
        cout<<RED<<endl<<"Non ci sono "<<N<<" parole"<<RESET;
        return "/err";
    }
    while(iss>>tmp){

        if(tmp==before){
            for(int i=0; i<N; i++) iss>>after;
        }
        after-=";";
    }
    return after;
}

string replace_content(string in, const char & start, const char & end, const char & sub=' '){
    int start_i=0, end_i=0;
    while(start_i<character_counter(in,start) and end_i<character_counter(in,end)){
        string repl=" ";
        string tmp= substr_CC(in, start_i + 1, end_i + 1, start, end);
        int s=tmp.size();
        for(int j=0; j<s-1; j++){ repl.push_back(' '); }
        in.replace(in.find(tmp), tmp.size(), repl);
        start_i++;
        end_i++;
    }
    return in;
}

string remove_content(string & in, const char & start, const char & end, bool & noErr){
    noErr=true;
    int i=(int)in.find(start)+1;
    bool kill=true;

    bool tmp;
    if(start!=end){
        tmp=(character_counter(in, start)+character_counter(in,end))%2==0;
    }else{
        tmp=character_counter(in, start)%2==0;
    }

    if(tmp) {
        for (; i < in.size() and i != 0; i++) {
            if (kill and in[i] != end) {
                in[i] = ' ';
            } else if (in[i] == end and kill) {
                kill = false;
            } else if (!kill and in[i] == start) {
                kill = true;
            }
        }
    } else noErr=false;

    return in;
}

void operator >> (const string & str, vector<string> & vec){
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
    int start=0, end=(int)in.size()-1;
    for(; in[start]==' '; start++){}
    for(; in[end]==' '; end--){}
    in=in.substr(start, end-start+1);

    return in;
}

template <typename T>
vector <int> order_vector_indexes( vector<T> input, const int & orden){
    int n= input.size();
    vector<bool> equal(n);
    vector<T> tmp = input;
    vector <int> output(n);

    sort(tmp.begin(), tmp.end());
    if(orden == -1) reverse(tmp.begin(), tmp.end());
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(tmp[i]==input[j] and !equal[j]){
                output[i]=j;
                equal[j]=true;
                j=n;
            }
        }
    }
    return output;
}

template <typename T>
bool between(const T & in, const T & val1, const T & val2){
    if(val1 < val2){
        return (in >= val1 and in <= val2);
    }
    else if(val1 > val2){
        return (in >= val2 and in <= val1);
    }
    else if(val1 == val2){
        return (in == val2);
    } else return false;
}

void get_cleanLine(ifstream & in, string & str){
    getline(in, str);
    replace_chars(str, {'\r', '\n'}, -1);
}



#endif