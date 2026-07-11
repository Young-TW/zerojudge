#include <iostream>

using namespace std;

typedef unsigned long long ull;
const ull M = 1000000009ULL;
const ull inv2 = 500000005ULL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ull N;
    while (cin >> N) {
        ull N_mod = N % M;
        ull ans = (N_mod * N_mod) % M;
        ull sum = 0;
        ull L = 1;
        while (L <= N) {
            ull v = N / L;
            ull R = N / v;
            ull L_mod = L % M;
            ull R_mod = R % M;
            ull v_mod = v % M;
            ull cnt_mod = (R_mod - L_mod + 1 + M) % M;
            ull sum_k_mod = (L_mod + R_mod) % M * cnt_mod % M * inv2 % M;
            sum = (sum + v_mod * sum_k_mod) % M;
            L = R + 1;
        }
        ans = (ans - sum + M) % M;
        cout << ans << "\n";
    }
    return 0;
}
