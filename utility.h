#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "Classes/Date/Date.h"
#include "Classes/Table/Table.h"

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

string substr_from_c_to_c(const string &in, const int &c1, const int &c2, const char &f1= ' ', const char &f2=' ', const bool &show_error=true) { //it return the sub string from the c1 character f1 to the c2 character f2, enter c1=0 to take from beginning and c2=-1 to take up to the end
    int start=0, end=1;
    int char1=0, i=0, char2=0;
    bool found1=false, found2=false;
    for(; i<in.size() and char2 != c2; i++){
        if(in[i] == f1){
            char1++;
        }
        if(in[i] == f2){
            char2++;
        }
        if(char1 == c1 and !found1){
            start=i+1;
            found1=true;
        }
    }

    if(in[i-1]==f2){
        found2=true;
    }

    end=i-1;
    if(c1==0){
        start=0;
    }
    if(c2==-1){
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

    if(substr_from_c_to_c(var, 1, 2, '"', '"', false)!="/err"){
        response = (to_check == "string");
    } else
    if(substr_from_c_to_c(var, 1, 2, 39, 39, false)!="/err"){ //char a=39 --> a='
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

bool cast_data(Table & table, const int & col_i, const string & type, const string & data){
    bool auto_increment_err=false;
    if(type=="int"){
        if((*static_cast<Column<int>*>(table.cols[col_i])).auto_increment){
            auto_increment_err=true;
        } else{
            (*static_cast<Column<int>*>(table.cols[col_i])).values.push_back(stoi(data));
        }
    } else
    if(type=="float"){
        (*static_cast<Column<float>*>(table.cols[col_i])).values.push_back(stof(data));
    } else
    if(type=="char"){
        (*static_cast<Column<char>*>(table.cols[col_i])).values.push_back(data[1]);
    } else
    if(type=="string"){
        string data_tmp=substr_from_c_to_c(data, 1, 2, '"', '"', false);
        (*static_cast<Column<string>*>(table.cols[col_i])).values.push_back(data_tmp);
    } else
    if(type=="time"){
        (*static_cast<Column<Time>*>(table.cols[col_i])).values.resize((*static_cast<Column<Time>*>(table.cols[col_i])).values.size()+1); //Increase Time vector of one
        (*static_cast<Column<Time>*>(table.cols[col_i])).values.end()->set_time(data);
    } else
    if(type=="date"){
        (*static_cast<Column<Date>*>(table.cols[col_i])).values.resize((*static_cast<Column<Date>*>(table.cols[col_i])).values.size()+1); //Increase Date vector of one
        (*static_cast<Column<Date>*>(table.cols[col_i])).values.end()->set_Date(data);
    }

    if(auto_increment_err){
        cerr<<endl<<"It isn't possible to enter data in a column if auto_increment was chosen for it!";
    }
    return auto_increment_err;
}

template<typename type> vector<type> operator -(vector<type> minuend, const vector<type> & subtrahend){
    for(int i=0; i<minuend.size(); i++){
        for(int j=0; j<subtrahend.size(); j++){
            if(minuend[i]==subtrahend[j]){
                for(int k=i; k<minuend.size()-1; k++){
                    minuend[k]=minuend[k+1];
                }
                minuend.resize(minuend.size()-1);
            }
        }
    }
    return minuend;
}

#endif