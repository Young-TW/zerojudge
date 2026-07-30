#include <bits/stdc++.h>
using namespace std;

const int MOD = 1234567;

// fast reading of a non‑negative integer, returns false on EOF
inline bool readInt(int &out) {
    int c = getchar_unlocked();
    if (c == EOF) return false;
    while (c < '0' || c > '9') {
        c = getchar_unlocked();
        if (c == EOF) return false;
    }
    int val = 0;
    while (c >= '0' && c <= '9') {
        val = val * 10 + (c - '0');
        c = getchar_unlocked();
    }
    out = val;
    return true;
}

int main() {
    int N;
    if (!readInt(N)) return 0;          // no input

    vector<int> dp(N + 1, 0);
    dp[1] = 1;                          // start city

    for (int i = 1; i <= N; ++i) {
        int M;
        readInt(M);
        for (int j = 0; j < M; ++j) {
            int v;
            readInt(v);                // destination, guaranteed v > i
            int sum = dp[v] + dp[i];
            if (sum >= MOD) sum -= MOD;
            dp[v] = sum;
        }
    }

    printf("%d\n", dp[N] % MOD);
    return 0;
}
