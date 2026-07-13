#include <iostream>

using namespace std;

long long pow3[35];

long long prefix(int K, long long x) {
    if (x == 0) return 0;
    if (x == (1LL << K)) return pow3[K];
    if (K == 0) return 0;
    long long mid = 1LL << (K - 1);
    if (x <= mid) {
        return 2 * prefix(K - 1, x);
    } else {
        return 2 * pow3[K - 1] + prefix(K - 1, x - mid);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    pow3[0] = 1;
    for (int i = 1; i <= 30; ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int K;
            long long A, B;
            cin >> K >> A >> B;
            long long ans = prefix(K, B) - prefix(K, A - 1);
            cout << "Case " << t << ": " << ans << "\n";
        }
    }
    
    return 0;
}
