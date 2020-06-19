
#include <iostream>
#include <string>
#include <Name.h>

using namespace std;

Name::Name():Nome("NonSpecificato"),Cognome("NonSpecificato");
Name::Name(string a,string b):Nome(a),Cognome(b);
Name::~Name(){};

void Name::setNome(string name){
    Nome=name;
}
void Name::setCognome(string co){
    Cognome=co;
}
string Studente::getNome(){
    return Nome;
}
string Studente::getCognome(){
    return Cognome;
}
