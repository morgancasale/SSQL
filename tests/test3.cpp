#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../utility.h"
using namespace std;


int main(){
    string a="ciaoo   mamma";

    remove_duplicate_chars(a, {' '});

    return 0;
}
