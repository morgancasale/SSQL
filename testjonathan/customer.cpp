#include <string.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

void input();
void id();
void name();
void age();
void address();
void salary();
void key();    //non so ancora a cosa ci possa servire quindi l'ho lasciato lì
void quit();
void displayall();
void search();

int main(){
    system("cls");                                                   //teoricamente prog morgan che si adatta
         int choice:
         cout << "1.Search customer" << endl;
         cout << "2.Exit program" << endl;
         cin >> choice;

    switch (choice){
        case 1:
            search();
            break;
        case 2:
            quit();
            break;

            cin.get();

        }
    }
void input() {
    long int salary;
    string name, address;
    int age, id;
    ofstream customer("file.txt", /*e qui sincero non sapevo cosa mettere */.....);  // nome file

    cout << "select" << endl;
    cin >> name;

    cout << "select" << endl;
    cin >> age;

    cout << "select" << endl;
    cin >> salary;

    cout << "select" << endl;
    cin >> id;

    cout << "select" << endl;
    cin >> address;

    customer << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;
    customer.close();
    main();
}

void name(){ /*---------------------------------------------------------------------------------------------------------name */

    ifstream customer("customer.txt");   //file chiamato totalmente a caso
    string name;
    string str;

    long int salary;
    string address;
    int age, id;
    system("CLS"); //pulire schermo
    cout << "select name";
    cin >> str;

    while (customer >> id >> name >> age >> address >> salary){
        if (str == name){

            system ("CLS");
            cout << " " << endl;
            cout << "id" << ' ' << "name" << ' ' << "age" << ' ' << "address" << ' ' << "salary" << endl;
            cout << "___________________" << endl;
            cout << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;

        }
        if(!(str == name)){
            system("cls");
            cout << "error" << endl;

        }
    }
    system ("pause");
    cin.get();
    main();
}

void address(){ /*------------------------------------------------------------------------------------------------------address*/

    ifstream customer("customer.txt");   //file chiamato totalmente a caso
    string address;
    string str;

    long int salary;
    string name;
    int age, id;
    system("CLS"); //pulire schermo
    cout << "select address";
    cin >> str;

    while (customer >> id >> name >> age >> address >> salary){
        if (str == address){

            system ("CLS");
            cout << " " << endl;
            cout << "id" << ' ' << "name" << ' ' << "age" << ' ' << "address" << ' ' << "salary" << endl;
            cout << "___________________" << endl;
            cout << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;

        }
        if(!(str == address)){
            system("cls");
            cout << "error" << endl;

        }
    }
    system ("pause");
    cin.get();
    main();
}

void age(){ /*----------------------------------------------------------------------------------------------------------age*/
    ifstream customer("customer.txt"); //file chiamato totalmente a caso
    string name, address;
    int age, id ;
    int fage;
    long int salary;
    system ("CLS");
    cout << "select age";
    cin >> fage;
    while (customer >> id >> name >> age >> address >> salary){
        if (fage == age){

            system ("CLS");
            cout << " " << endl;
            cout << "id" << ' ' << "name" << ' ' << "age" << ' ' << "address" << ' ' << "salary" << endl;
            cout << "___________________" << endl;
            cout << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;

        }
        if(fage != age){
            system("CLS");
            cout << "error" << endl;

        }
    }
    system ("pause");
    cin.get();
    main();

}

void id(){ /*-----------------------------------------------------------------------------------------------------------id*/
    ifstream customer("customer.txt"); //file chiamato totalmente a caso
    string name, address;
    int age, id ;
    int fid;
    long int salary;
    system ("CLS");
    cout << "select age";
    cin >> fid;
    while (customer >> id >> name >> age >> address >> salary){
        if (fid == id){

            system ("CLS");
            cout << " " << endl;
            cout << "id" << ' ' << "name" << ' ' << "age" << ' ' << "address" << ' ' << "salary" << endl;
            cout << "___________________" << endl;
            cout << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;

        }
        if(fid != id){
            system("CLS");
            cout << "error" << endl;

        }
    }
    system ("pause");
    cin.get();
    main();

}

void salary(){ /*-------------------------------------------------------------------------------------------------------salary*/
    ifstream customer ("customer.txt"); //file chiamato totalmente a caso
    string name, address;
    int age, id;
    long int salary;
    long int fsalary;
    system("CLS");
    cout << "select" ;
    cin >> fsalary;
    while (customer >> id >> name >> age >> address >> salary){
        if (fsalary == salary){

            system ("CLS");
            cout << " " << endl;
            cout << "id" << ' ' << "name" << ' ' << "age" << ' ' << "address" << ' ' << "salary" << endl;
            cout << "___________________" << endl;
            cout << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;

        }
        if(fsalary != salary){
            system("CLS");
            cout << "error" << endl;

        }
    }
    system ("pause");
    cin.get();
    main();
}
void quit(){ /*---------------------------------------------------------------------------------------------------------quit*/
    system ("CLS");
    cout << "EXIT programm" << endl;
    system("pause");
    cin.get();
}

void displayall(){
    ifstream customer("customer.txt");
    int age, id;
    string name, address;
    long int salary;
    system("CLS");
    cout << "customers:" << endl;
    cout << "id" << ' ' << "name" << ' ' << "age" << ' ' << "address" << ' ' << "salary" << endl;
    cout << "___________________" << endl;
    while (customer >> id >> name >> age >> address >> salary) {
        cout << id << ' ' << name << ' ' << age << ' ' << address << ' ' << salary << endl;
    }
    system ("pause");
    cin.get();
    main();

}

void search() {
    int choice2;
    system("CLS");

    cout << "1.Search by name" << endl;
    cout << "2.Search by address" << endl;
    cout << "3.Search by age" << endl;
    cout << "4.Search by id" << endl;
    cout << "5.Search by salary" << endl;
    cout << "6.display all customers" << endl;
    cout << "7.Exit program" << endl;
    cin >> choice2;

    switch (choice2) {
        case 1:
            name();
            break;
        case 2:
            address();
            break;
        case 3:
            age();
            break;
        case 4:
            id();
            break;
        case 5:
            salary();
            break;
        case 6:
            displayall();
            break;
        case 7:
            quit();
            break;

    }
}


// questo imbasso da vedere meglio

char orden = “a”;  /* a: ascendente d: descendente */

    for (i=0; i<n-1; i++)
    {
        for (j=i+1; j<n; j++)
        {
            switch(orden)
            {case "a":
                if(strcmp(Vector[i],Vector[j])>0)
                {
                    aux  = Vector[i];
                    Vector[i] = Vector[j];
                    Vector[j] = aux;
                }
                break;
                case "d":
                    if(strcmp(Vector[i],Vector[j])<0)
                    {
                        aux  = Vector[i];
                        Vector[i] = Vector[j];
                        Vector[j] = aux;
                    }
                    break;
            }
        }
    }











