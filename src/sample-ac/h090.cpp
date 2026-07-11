#include <iostream>
#include <string>

using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string S;
    while (cin >> S) {
        int N = S.length();
        long long pow2;
        if (N == 1) {
            pow2 = 499122177; // 2^-1 mod 998244353
        } else {
            pow2 = power(2, N - 2);
        }
        
        long long p5 = 1;
        long long sum_p5 = 1;
        long long ans = 0;
        
        for (int i = N - 1; i >= 0; --i) {
            int digit = S[i] - '0';
            long long term = (digit * ((p5 + sum_p5) % MOD)) % MOD;
            ans = (ans + term) % MOD;
            
            p5 = (p5 * 5) % MOD;
            sum_p5 = (sum_p5 * 5 + 1) % MOD;
        }
        
        ans = (ans * pow2) % MOD;
        cout << ans << "\n";
    }
    return 0;
}
