#include <iostream>
#include <fstream>
#include "Time.h"
using namespace std;

class ciao{
    public:
        int a, b,c;
};

int main(){
    ofstream file;
    file.open("test.txt", ios::app);
    if(!file){
        cout<<"err";
    }

    ciao a;
    a.a=1;
    a.b=3;
    a.c=5;
    file.write((char*)&a, sizeof(a));
    file.close();

    ifstream file2;
    file2.open("test.txt", ios::in);
    ciao c;
    file2.read((char*)&c, sizeof(c));

    file.close();
}
