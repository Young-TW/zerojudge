#include <iostream>
using namespace std;

int a,b;

int gcd(int a,int b){
    while(b>0){
        if(a>b){
            a = a%b;
        }else{
            swap(a,b);
        }
    }
    return a;
}

int main(){
    cin >> a >> b;
    cout << gcd(a,b);
    return 0;
}