#include <iostream>
#include "../utility.h"
#include "../syntax.h"
using namespace std;

string ron(string in, const int &c1, const int &c2, const char &f1= ' ', const char &f2=' ') { //it return the sub string from the c1 character f1 to the c2 character f2, enter c1=0 to take from beginning and c2=-1 to take up to the end
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
    }

    if(!found1 or !found2){ //if one or two characters aren't found then the function returns "/err"
        cerr<<endl<<"One or the two characters weren't found!";
        return "/err"; //Maybe we should add an exception for the use of "/err" as any name
    } else{
        return in.substr(start,end-start);
    }
}


bool g(string in, const bool &show_err=true){
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

    return err;
}

int main(){
    string b="CREATE TABLE CUSTOMERS ( ID INT NOT NULL, NAME TEXT NOT NULL, AGE INT NOT NULL, ADDRESS TEXT , SALARY FLOAT, PRIMARY KEY (ID) );";

    cout<<substr_from_c_to_c(b, 2, 3, false);
    clean_input(b);

    /*bool c;
    if(c=check_CREATE_syntax(b)){
        cout<<"1st test -> success";
    }*/
    vector<string> data=get_CREATE_data(b);
    cout<<b;
    return 0;
}
