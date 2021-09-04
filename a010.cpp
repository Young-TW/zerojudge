#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int count = 2;
    while(n>count){
        if(n%count!=0){
            n = n/count;
        }
        count++;
    }
    return 0;
}