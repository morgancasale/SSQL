#include <iostream>
#include "../Classes/Table/Table.h"
using namespace std;

int main(){
    Table t;
    t.create_col("id int");
    cout<<"w";
    return 0;
}

/*
    vector<void *> a;
    static vector<int> j;
    j.resize(2);
    col<string> g;
    g.set_value("mamma");
    int b=3;
    float c=3.45;
    vector<int> e={1,2,3,4};
    a.resize(3);
    a[0]=static_cast<void *>(&e);
    a[1]=static_cast<void *>(&c);
    a[2]= static_cast<void *>(&g);
    cout<< (*static_cast<vector<int>*>(a[0]))[2] << " " << *static_cast<float *>(a[1])<<" ";
    cout<< (*static_cast<col<string> *>(a[2])).get_value();
 */

/*string b="CREATE TABLE CUSTOMERS ( ID INT NOT NULL, NAME TEXT NOT NULL, AGE INT NOT NULL, ADDRESS TEXT , SALARY FLOAT, PRIMARY KEY (ID) );";
    clean_input(b);
    cout<<substr_from_c_to_c(b, 2, 3, ' ', ' ',false);

    bool c;
    if(c=check_CREATE_syntax(b)){
        cout<<"1st test -> success";
    }
    vector<string> data=get_CREATE_data(b);
    cout<<b;*/