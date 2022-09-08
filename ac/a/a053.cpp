#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    if(n>=40)
        cout << "100";
    else if(n<=10)
        cout << 6*n;
    else if(n<=20)
        cout << 60 + ((n-10)*2);
    else if(n<40)
        cout << 80 + (n-20);
    return 0;
}