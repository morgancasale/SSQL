//
// Created by Morgan Casale on 25/05/2020.
//

#ifndef CS_PROJECT_CORE_H
#define CS_PROJECT_CORE_H
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

//remove char sub from string then returns a stringstream from the modified input string
stringstream data_ss(string in, const char &sub){
    replace(in.begin(), in.end(), sub, ' ');
    stringstream ss(in);
    return ss;
}
#endif //CS_PROJECT_CORE_H
