#include<iostream>
#include<fstream>

/* The useful classes for working with files in C++ are : 
1.) fstreambase
2.) ifstream -> input fstream. derived from fstrambase
3.) ofstream -> output fstream. derived from fstreambase
 */

/* in order to work with files in C++,you will have to open it. 
Primarily, There are 2 ways to open a file :
1.) Using the constructor
2.) Using the member function open() of the class 
*/ 
using namespace std;

int main(){

    string name;
    ofstream file;
    file.open("test01A.txt");
    //Operning file using constructor and writing it
    // ofstream out("test01.txt"); //write operation
    //out <<st;

    //Operning file using constructor and reading it 
    //read operation
    // in >> st1;
    cout << " Enter your name : " <<endl;
    getline(cin,name);

    file <<" Welcome " <<name <<endl;

    file.close();
}