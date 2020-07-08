#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
template <typename type> class list:std::list<type>{
public:
    type & operator [] (const int & pos){
        auto it=this->begin();
        std::advance(it, pos);
        return *it;
    }
    void copy (const std::list<type> & in){
        this->assign(in.begin(), in.end());
    }
};
int main(){
    std::vector<int> a={1,2,3,4};
    std::list<int> b={1,2,3,4};
    list<int> c;
    c.copy(b);
    std::cerr<<a[2]<<c[2];

    return 0;
}