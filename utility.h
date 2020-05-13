#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H
#endif //CS_PROJECT_UTILITY_H
using namespace std;
#include <algorithm>
#include <sstream>
#include "Classes/Database/Database.h"

stringstream data_ss(string in, const char &sub){
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

string substr_from_s_to_s(string in, int s1, int s2){ //it return the sub string from the space s1 to the space s2, enter 0 to take from beginning and -1 to take up to the end

}