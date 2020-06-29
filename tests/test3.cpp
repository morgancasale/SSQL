#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../utility.h"
using namespace std;


int main(){
    string a="asasas -dsdasfsdfgò-  - dfgj  -dsfsdfsdf- jgd";
    bool b;
    a=remove_content(a, '-', '-', b);
    b=true;
    for(int i=0; b; i++){
        cout<<i;
        b= false;
    }
    cout<<" ciao";


    return 0;
}