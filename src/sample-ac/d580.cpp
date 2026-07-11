#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAX_N = 10001;
    const int MOD = 2012;
    int fib[MAX_N];
    
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < MAX_N; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
    
    int n;
    while (cin >> n) {
        cout << fib[n] << "\n";
    }
    
    return 0;
}
