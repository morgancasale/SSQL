#include <iostream>
#include <vector>
#include <list>
#include "../utility.h"
using namespace std;


int main(){
    static vector<int> a;
    void * tmp= static_cast<void *>(&a);
    (*static_cast<auto *>(tmp))
    cout<<"a";
    return 0;
}