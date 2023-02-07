#include <iostream>
using namespace std;

void printNum(int num){
    for(int i=0;i<num;i++)
        cout << num;
    cout << endl;
}

int main(){
    int n,a,f;
    cin >> n;
    while(n>0){
        cin >> f >> a;
        for(int k=0;k<=a;k++){
            for(int j=0;j<f;j++)
                printNum(j);
            for(int j=f;j>0;j--)
                printNum(j);
            cout << endl;
        }
        n--;
    }
    return 0;
}

// 00488 - Triangle Wave