#include <iostream>
#include <vector>
#include "../utility.h"
using namespace std;

class miao{
public:
    int i;
    miao(int a){
        i=a;
    }
};

int main(){
    vector<miao> ciao;
    ciao.resize(1);
    ciao.end()= miao &a(4);
    return 0;
}
