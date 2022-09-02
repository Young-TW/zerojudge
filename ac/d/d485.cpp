#include <iostream>
using namespace std;

int main(){
    int a,b,x;
    cin >> a >> b;
    bool c;
    c = a%2==1 && b%2==1;
    x = (b-a)/2+1-c;
    cout << x;
    return 0;
}