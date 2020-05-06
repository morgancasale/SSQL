#ifndef CS_PROJECT_UTILITY_H
#define CS_PROJECT_UTILITY_H
#endif //CS_PROJECT_UTILITY_H
using namespace std;
#include <algorithm>
#include <sstream>

stringstream data_ss(string in, const char &sub){
    replace(in.begin(), in.end(), sub, ' ');
    stringstream ss(in);
    return ss;
}