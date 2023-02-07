#include <iostream>
using namespace std;

int f(int i){
    if(i == 1 || i == 0){
        return 1;
    }
    return (i-1 + f(i-1));
}

int main(){
    int n;
    while(cin >> n){
        cout << f(n) << endl;
    }
    return 0;
}