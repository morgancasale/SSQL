
#ifndef CS_PROJECT_NAME_H
#define CS_PROJECT_NAME_H

#include <iostream>
#include<string>

using namespace std;

class Name{
public:
    Name();
    Name(string,string);
    ~Name();

    Name operator+(const Name&) const;
    void setNome(string);
    void setCognome(string);


    string getNome();
    string getCognome();


private:
    string Nome;
    string Cognome;

};

#endif