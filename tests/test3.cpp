#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../src/utility.h"
#include "../src/syntax.h"
#define RED     "\033[31m"
#define RESET   "\033[0m"
using namespace std;
int main(){
    vector<int> a={1,2,1,1,1,2,2,2,2,3,4,1,5,6,5,5,6,6};
    remove_duplicateEls(a);

    return 0;
}