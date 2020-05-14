#include <iostream>
#include <vector>
#include "../utility.h"
using namespace std;


int main(){
    string a="ciao mamma come stai";
    cout<<substr_from_c_to_c(a, 0,3, 'a');
    return 0;
}
