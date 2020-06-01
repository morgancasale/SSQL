#include <iostream>
#include <vector>
#include "../utility.h"
using namespace std;

int main(){
    vector<string> minuend={"name", "yor", "price", "sef"};
    vector<string> subtrahend={"yor", "name", "sef"};
    minuend=minuend-subtrahend;
    cout<<"a";
    return 0;
}