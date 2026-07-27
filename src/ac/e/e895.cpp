#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MOD = 10007;
    const int MAXL = 100000;               // maximum L
    static int pow2[MAXL + 1];
    pow2[0] = 1;
    for (int i = 1; i <= MAXL; ++i) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    long long L;
    while (cin >> L) {
        // L >= 1 according to problem statement
        cout << pow2[L - 1] << '\n';
    }
    return 0;
}
