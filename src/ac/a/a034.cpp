#include <iostream>
using namespace std;

void toBinary(int num){
    int i;
    int ar[32];
    for(i=0;num>0;i++){
        ar[i] = num%2;
        num=num/2;
    }
    for(int n=i-1;n>=0;n--){
        cout << ar[n];
    }
    cout << endl;
    return;
}

int main(){
    int num;
    while(cin >> num){
        toBinary(num);
    }
    return 0;
}