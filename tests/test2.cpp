#include <iostream>
#include <vector>
#include <list>
#include "../utility.h"
#include "../syntax.h"
using namespace std;


int main(){
    string a="UPDATE CUSTOMERS SET SALARY = 12000, NAME = \"Morgan\" WHERE AGE = 20;";
    take_command(a);
    if(control_update(a)){
        cout<<":)";
    }
    return 0;
}