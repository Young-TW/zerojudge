#include <iostream>
using namespace std;

int main(){
    char pw[7];
    cin >> pw;
    for(int i=0;i<6;i++){
        cout << abs(pw[i] - pw[i+1]);
    }
    return 0;
}