#include <iostream>
using namespace std;

int main(){
    int f,l,n;
    cin >> f >> l >> n;
    for(int i=f;i<=l;i+=n){
        cout << i << " ";
    }
    return 0;
}