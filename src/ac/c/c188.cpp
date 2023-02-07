#include <iostream>
using namespace std;

long long p[201];

int main(){
    p[0] = 1;
    for(int i=1;i<=200;i++)
        for(int j=i;j<=200;j++)
            p[j] += p[j-i];
    int n;
    while(cin >> n)
        cout << p[n] << endl;
    return 0;
}