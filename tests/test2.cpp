#include <iostream>
#include <vector>
using namespace std;

template<typename type> class Column{
public:
    vector<type> values;
    string key;
    bool not_null;
    bool auto_increment;
};

int main(){
    Column<int> a;
    a.key="ciao";
    Column<int> b;
    b.key=",mhd";
    Column<string> c;
    c.key="fsadf";
    Column<string> d;
    c.key="fsadf";
    vector<void *> test;

    test.push_back(static_cast<void *>(&a));
    test.push_back(static_cast<void *>(&c));
    test.push_back(static_cast<void *>(&b));
    test.push_back(static_cast<void *>(&d));
    cout<<"a";
    return 0;
}