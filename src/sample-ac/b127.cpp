#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long fib[50] = {0};
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= 46; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    int n;
    while (cin >> n) {
        cout << fib[n + 1] << "\n";
    }
    
    return 0;
}
