#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Classes/Date/Date.h"


string tolower(string &in, int stop= -1){ //converts all upper letters of a string to lower ones
    stop = ((stop<0)? (int)in.size()-1 : stop); //if stop<0 takes all the string
    for(int i=0; i<=stop; i++){
        in[i]=tolower(in[i]);
    }
    return in;
}/** O(xn) */

// it return the substring from the n(counter1) instance of char1
// to the n(counter2) instance of char2
// tricks: counter1=0 to take from beginning ignoring char1
//         and counter2=-1 to take up to the end ignoring char2
string substr_CC(const string &in, const int &counter1, const int &counter2, const char &char1= ' ', const char &char2= ' ') {
    int start=0, end=1;
    int tmpCounter1=0, i=0, tmpCounter2=0;
    bool found1=false, found2=false;
    if(counter1==0 and counter2==-1){
        start=0;
        end=in.size();
        found1=true;
        found2=true;
    } else{
        for (; i < in.size() and tmpCounter2 != counter2; i++) { /** O(x) */
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
} /** O(n) */

int character_counter(const string & in, char char_to_count){
    int counter=0;
    for(char c:in){
        if(c==char_to_count) counter++;
    }
    return counter;
} /** O(in.size) --> O(x) */

bool remove_duplicate_chars(string & in, const vector<char> & c, const bool & show_err=true){
    bool err=false;

    for(const char & tmp: c){
        int first_c=in.find(tmp); /*finds the position of the first occurrence of the character tmp*/ /** O(n) */
        if(first_c != -1){//find returns -1 if the characters isn't found
            int found=0;
            for(int i= first_c + 1; i < in.size(); i++){ //Loops over all characters of the input starting from first_c
                if((in[i]!=in[first_c]) or (in[i] != tmp)){
                    first_c++;
                    in[first_c]=in[i];
                } else{
                    found++;
                }
            } /** O(n) */
            in.resize(in.size()-found); /** O(n) */
        } else{
          err=true;
        }
    }/** O(3xn) */

    if(err and show_err){
        cerr<<"Can't find one or more of the characters to delete!"<<endl;
    }
    return err;
} /** O(xn) */

string replace_chars(string &in, const vector<char> & sub, const char &car) {
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
} /** O(sub.size()*n*(n+n)) --> O(xn^2) */

unsigned long int find_nIteration(string in, const string & search, const int & it){
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

bool clean_input(string & in, const vector<string> & programKeyWords){
    string tmp=in;
    tolower(tmp);
    for(const string & a: programKeyWords) {
        unsigned long int pos=0;
        if(tmp.find(a)!=-1) {
            for (int i = 1; (pos = find_nIteration(tmp, a, i)) != -1; i++) {
                unsigned long int val = pos + a.size();
                bool flag = (tmp[val]==' ' or tmp[val]==',' or tmp[val]==')' or tmp[val]=='(');
                flag &=(pos==0) or (tmp[pos-1]==' ' or tmp[pos-1]==',' or tmp[pos-1]==')' or tmp[pos-1]=='(');

                if (flag) {
                    in.replace(pos, a.size(), a); /** O(n^2) */
                }
            }
        }
    } /** O(programKeyWords.size()*n^2) --> O(p*n^2) */
    replace_chars(in, {'\n', '\t', '\r'}, ' '); /** O(3n^2) */
    return remove_duplicate_chars(in, {' '}, false); /** O(3n) */
} /** O(xn^2) */

string erase_substr(string &in, const string & to_erase){
    int pos=in.find(to_erase);
    if(pos!=-1){
        in.erase(pos, to_erase.size()); /** O(n) */
        replace_chars(in, {'\n'}, ' '); /** O(n^2) */ //we should delete this line
    }
    return in;
} /** O(n^2) */

string operator -(string minuend, const string & subtrahend){
    return erase_substr(minuend, subtrahend);
} /** O(n^2) */

void operator -=(string & minuend, const string & subtrahend){
    erase_substr(minuend, subtrahend);
} /** O(n^2) */

string substr_SS(string in, string s1, string s2, const bool & reverse= false, bool fromZero= false){
    int start, end;
    //int shift = 1;
    if(s1.empty()){ start=0; }
    int shift = s1.size();
    if(fromZero){ shift=0; }

    if(reverse){
        std::reverse(in.begin(), in.end()); /** O(n) */
        std::reverse(s1.begin(), s1.end()); /** O(n) */
        std::reverse(s2.begin(), s2.end()); /** O(n) */
        start = (int)in.find(s2) + shift; /** O(n) */
        end = in.find(s1); /** O(n) */
    } else{
        start = (int)in.find(s1) + shift; /** O(n) */
        end = in.find(s2); /** O(n) */
    }

    string out=in.substr(start, end - start); /** O(n) */
    if(start==-1 or end==-1){
        return "/err";
    }
    else{
        if(reverse){ std::reverse(out.begin(), out.end()); } /** O(n) */
        return out;
    }
} /** O(9n) */

bool isalphanum(const char & in){ return isalnum(in) or isalpha(in); }

int num_of_words(string in){
    int num=0, i=0, k=0, end=(int)in.size()-1;

    for(; !isalphanum(in[end]); end--){} /** O(in.size()) --> O(x) */
    end++;
    in=in.substr(0, end); /** O(n) */
    in.push_back(' ');

    if(!isalphanum(in[0]) and !isalphanum(in[in.size()-1])){ /** O(2x) */
        i++;
        k++;
    }

    for(; i<in.size()-k; i++){ /** O(x) */
        for(; isalphanum(in[i]); i++){} /** O(x) */
        if(i!=0 and isalphanum(in[i-1])){ /** O(x) */
            num++;
        }
    }/** O(2x^2) */
    if(num==0 and isalphanum(in[in.size()-1])){ num++; } /** O(x) */

    char characters[2]={'_', '-'};
    while(in.find('_')!=-1 or in.find('-')!=-1){ /** O(2n) */
        for(const char & ch: characters){ /** O(x) */
            int pos=in.find(ch); /** O(n) */
            if (pos != -1) {
                if (isalphanum(in[pos - 1]) and isalphanum(in[pos + 1])) { /** O(2x) */
                    num--;
                }
                in[pos] = ' ';
            }
        }
    } /** O(2n^2) */

    return num;
} /** O(2n^2) */

bool is_a_Time(const string & var){
    bool response=true;

    int hours=-1, min=-1, sec=-1;
    int tmp=0;

    char sub;
    if(var.find(':')!=-1 and character_counter(var, ':')<3){ /** O(n) */
        sub=':';
    }
    else if(var.find('.')!=-1 and (tmp=character_counter(var, '.')==1 or tmp==2)){ /** O(n) */
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
} /** O(2n) */

bool is_a_Date(const string & var){
    bool response=true;

    int day=-1, month=-1, year=-1;

    char sub;
    bool err=false;
    if(var.find('-')!=-1 and character_counter(var, '-')==2){ /** O(n) */
        sub='-';
    } else if(var.find('.')!=-1 and character_counter(var, '.')==2){ /** O(n) */
        sub='.';
    } else if(var.find('/')!=-1 and character_counter(var, '/')==2){ /** O(n) */
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
} /** O(3n) */

//The first parameter is the input data while the second one is the type to check
bool check_data_consistence(const string & var, const string & type){
    bool noErr=false;

    if(substr_CC(var, 1, 2, '"', '"') != "/err"){ /** O(n) */
        noErr = (type == "string" or type == "text");
    } else
    if(substr_CC(var, 1, 2, 39, 39) != "/err"){ /** O(n) */ //char a=39 --> a='
        noErr = (type == "char");
    } else
    if(var.find('.')!=-1){ /** O(n) */
        bool Date_resp=is_a_Date(var);
        bool Time_resp=is_a_Time(var);
        if((Time_resp) and !(Date_resp)){ /** O(5n) */
            noErr = (type == "time");
        }
        else if(Date_resp){
            noErr = (type == "date"); }
        else{
            noErr = (type == "float"); }
    } else
    if(var.find(':')!=-1){ /** O(n) */
        bool Date_resp=is_a_Date(var);
        if(is_a_Time(var) and !(Date_resp)){ noErr = (type == "time"); } /** O(3n) */
        else if(Date_resp){ noErr = (type == "date"); }
    } else
    if(var.find('/')!=-1){ noErr = (type == "date"); } /** O(n) */
    else if(character_counter(var,'-')==2){ noErr = (type == "date"); }
    else{
        noErr = (type == "int");
    }

    return noErr;
} /** O(14n) */

template<typename type> vector<type> operator -(vector<type> minuend, const vector<type> & subtrahend){

    for(int i=0; i<subtrahend.size(); i++){ /** O(x) */
        type sub=subtrahend[i];//prendo un sottraendo
        bool found=false;
        for(int j=0; j<minuend.size() and !found; j++){ /** O(y) */
            type min=minuend[j]; //prendo il minuendo
            if(min==sub){
                for(int k=j; k<minuend.size()-1; k++){ /** O(y) */
                    minuend[k]=minuend[k+1];
                }
                minuend.resize(minuend.size()-1);
                found=true;
            }
        }
    }
    return minuend;
}/** O(xy^2) */

template<typename type> void operator -=(vector<type> & minuend, const vector<type> & subtrahend){
    for(int i=0; i<subtrahend.size(); i++){ /** O(x) */
        type sub=subtrahend[i];//prendo un sottraendo
        bool found=false;
        for(int j=0; j<minuend.size() and !found; j++){ /** O(y) */
            type min=minuend[j]; //prendo il minuendo
            if(min==sub){
                for(int k=j; k<minuend.size()-1; k++){ /** O(y) */
                    minuend[k]=minuend[k+1];
                }
                minuend.resize(minuend.size()-1);
                found=true;
            }
        }
    }
} /** O(xy^2) */

template<typename type> void deleteElements_from_vec(vector<type> & minuend, const vector<int> & rows){
    for(int k : rows){ /** O(n) */
        for(; k<minuend.size()-1; k++){ /** O(x) */
            minuend[k]=minuend[k+1];
        }
        minuend.resize(minuend.size()-1);
    }
}/** O(x*n) */

string take_the_N_nextWord(const string & in, string before, int N){
    string tmp, after;
    stringstream iss(in);
    if(before.empty()){
        before=substr_CC(in, 0, 1, 0, ' ');
        replace_chars(before, {' '}, -1);
    } if(in.find(before)==-1){ /** O(n) */
        cerr<<endl<<"La parola non esiste nella frase";
        return "/err";
    }
  
    if(N<=0 or N>in.size()){
        cerr<<endl<<"Non ci sono "<<N<<" parole";
        return "/err";
    }
    while(iss>>tmp){ /** O(n) */

        if(tmp==before){
            for(int i=0; i<N; i++) iss>>after;
        }
        after-=";";
    }
    return after;
} /** O(2n) */


int num_of_chars(const string & in, const char & c){
    int num=0;
    for(const char tmp: in){
        if(tmp==c){ num++; }
    }
    return num;
} /** O(x) */

string replace_content(string in, const char & start, const char & end, const char & sub=' '){
    int start_i=0, end_i=0;
    while(start_i<num_of_chars(in,start) and end_i<num_of_chars(in,end)){ /** O(x) */
        string repl=" ";
        string tmp= substr_CC(in, start_i + 1, end_i + 1, start, end); /** O(n) */
        int s=tmp.size();
        for(int j=0; j<s-1; j++){ repl.push_back(' '); } /** O(y) */
        in.replace(in.find(tmp), tmp.size(), repl); /** O(n) */
        start_i++;
        end_i++;
    }
    return in;
} /** O(xn^2) */

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

void operator>>(const string & str, vector<string> & vec){
    vec.resize(0);
    stringstream ss(str);
    string tmp;
    ss>>tmp;
    while(!tmp.empty()){ /** O(n) */
        vec.push_back(tmp);
        tmp="";
        ss>>tmp;
    }
} /** O(n) */

string removeSpaces_fromStart_andEnd(string & in){
    int start=0, end=(int)in.size()-1;
    for(; in[start]==' '; start++){} /** O(x) */
    for(; in[end]==' '; end--){} /** O(x) */
    in=in.substr(start, end-start+1);

    return in;
} /** O(2x) */

template <typename T>
vector <int> order_vector_indexes(const vector<T> & input, const int & orden){
    /* +1=ascending; -1=descending */
    int n=input.size(), aux=0;
    vector <int> output(n);

    for (int i=0; i<n; i++){
        aux=0;
        for (int j=0; j<n; j++){
            if(input[i]>input[j] and orden==+1) aux++;
            else if(input[i]<input[j] and orden==-1)  aux++;
            else if(input[i]==input[j]) aux = j==i ? aux : aux+1;
            else if(!orden) cerr<<endl<<"errore";
        }
        output[aux]=i;
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

/*template<typename type> bool check_existence(const vector<type> &vec, const type &el){
    bool found=false;
    for(const type &x : vec){
        if(x==el){ found=true; }
    }
    return found;
}*/

#endif