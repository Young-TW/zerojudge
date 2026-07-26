#include <iostream>

using namespace std;

const int MOD = 1000000007;

int S[10005];
int T[10005];
long long pow2[10005];

long long f_iter(int n, int target) {
    long long res = 0;
    int cur_target = target;
    for (int i = n; i >= 1; i--) {
        if (S[i] == cur_target) continue;
        int other = 6 - S[i] - cur_target;
        res = (res + pow2[i - 1]) % MOD;
        cur_target = other;
    }
    return res;
}

long long g_iter(int n, int source) {
    long long res = 0;
    int cur_source = source;
    for (int i = n; i >= 1; i--) {
        if (T[i] == cur_source) continue;
        int other = 6 - T[i] - cur_source;
        res = (res + pow2[i - 1]) % MOD;
        cur_source = other;
    }
    return res;
}

long long h_iter(int n) {
    for (int i = n; i >= 1; i--) {
        if (S[i] != T[i]) {
            int other = 6 - S[i] - T[i];
            return (f_iter(i - 1, other) + 1 + g_iter(i - 1, other)) % MOD;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    pow2[0] = 1;
    for (int i = 1; i <= 10000; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
    int N;
    while (cin >> N && N) {
        for (int i = 1; i <= N; i++) {
            cin >> S[i];
        }
        for (int i = 1; i <= N; i++) {
            cin >> T[i];
        }
        cout << h_iter(N) << "\n";
    }
    return 0;
}
