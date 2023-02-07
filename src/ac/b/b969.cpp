#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string s1, s2, name;
    getline(cin, s1);
    getline(cin, s2);
    stringstream ss(s1);
    while (ss >> name)
        cout << s2 <<", "<< name <<endl;
    return 0;
}