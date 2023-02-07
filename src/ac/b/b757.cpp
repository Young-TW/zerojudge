#include <iostream>
using namespace std;

int main(){
    double r;
    while(cin >> r){
        r*=9;
        r/=5;
        r+=32;
        cout << r << endl;
    }
    return 0;
}