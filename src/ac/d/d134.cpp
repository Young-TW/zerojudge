#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M && (N || M)) {
        int K = min(M, N - M);
        unsigned long long ans = 1;
        for (int i = 1; i <= K; ++i) {
            unsigned long long num = N - K + i;
            unsigned long long den = i;
            
            unsigned long long g1 = gcd(ans, den);
            ans /= g1;
            den /= g1;
            
            unsigned long long g2 = gcd(num, den);
            num /= g2;
            den /= g2;
            
            ans *= num;
        }
        cout << N << " things taken " << M << " at a time is " << ans << " exactly.\n";
    }
    return 0;
}
