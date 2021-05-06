#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int i=2;
    while (i<n){
        while(1){
            if (n%i == 0){
                n=n/i;
            }
            else{
                break;
            }
        }
        i++;
    }
    return 0;
}