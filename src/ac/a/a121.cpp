#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long n){
    if(n < 2) return false;
    if(n < 4) return true;
    if(n % 2 == 0) return false;
    for(long long i = 3; i * i <= n; i += 2)
        if(n % i == 0) return false;
    return true;
}

int main(){
    long long a, b;
    while(cin >> a >> b){
        int cnt = 0;
        for(long long i = a; i <= b; i++)
            if(isPrime(i)) cnt++;
        cout << cnt << "\n";
    }
    return 0;
}
