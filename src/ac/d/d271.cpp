#include <iostream>

using namespace std;

short fib[1001][6005];
int pisano[1001];

void preprocess() {
    for (int n = 1; n <= 1000; ++n) {
        if (n == 1) {
            pisano[1] = 1;
            fib[1][0] = 0;
            fib[1][1] = 0;
            continue;
        }
        fib[n][0] = 0;
        fib[n][1] = 1 % n;
        int prev = 0, curr = 1 % n;
        for (int i = 1; i <= 6 * n; ++i) {
            int next = (prev + curr) % n;
            fib[n][i + 1] = next;
            prev = curr;
            curr = next;
            if (prev == 0 && curr == 1 % n) {
                pisano[n] = i;
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    preprocess();
    
    int t;
    if (!(cin >> t)) return 0;
    
    while (t--) {
        unsigned long long a, b;
        int n;
        cin >> a >> b >> n;
        
        int mod = pisano[n];
        unsigned long long base = a % mod;
        unsigned long long exp = b;
        unsigned long long res = 1;
        
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        
        int idx = (int)res;
        cout << fib[n][idx] << "\n";
    }
    
    return 0;
}
