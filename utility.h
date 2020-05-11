#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H

using namespace std;
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

stringstream data_ss(string in, const char &sub){
    replace(in.begin(), in.end(), sub, ' ');
    stringstream ss(in);
    return ss;
}

#endif //CS_PROJECT_UTILITY_H