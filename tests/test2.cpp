#include <iostream>
#include <vector>
#include <list>
#include "../utility.h"
using namespace std;


int main(){
    vector<int> a= {1,2,3};
    deleteElements_from_vec(a, {0, 2});

    return 0;
}