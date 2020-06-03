#include <iostream>
#include <vector>
#include <list>
#include "../utility.h"
using namespace std;

int main(){
    static vector<vector<int>> a;
    for(int i=0; i<10; i++){
        vector<int> b;
        int c = *new int;
        b.push_back(*new int);
        a.push_back(b);
    }
    cout<<"a";
    return 0;
}