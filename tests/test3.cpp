#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../utility.h"
using namespace std;


int main(){
    string a = "ciao";
    a.erase(2,2);
    string b = "from ciao where";
    b=substr_from_s_to_s(b, "from", "where", false, true);

    return 0;
}
