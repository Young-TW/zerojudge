#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    string str;
    cin >> str;
    string str2 = str;
    reverse(str2.begin(),str2.end());
    if(str==str2){
        cout << "yes";
    }else{
        cout << "no";
    }
    return 0;
}