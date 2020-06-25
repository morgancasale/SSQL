#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../utility.h"
using namespace std;


int main(){
    string a = "ciao";
    a.erase(2,2);
    string b = "primary key(name) )";
    b.erase(18,1);

    return 0;
}
