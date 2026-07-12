#include <iostream>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    int M;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;
        vector<long long> S(M);
        for (int i = 0; i < M; ++i) {
            cin >> S[i];
        }
        
        long long ans = N;
        for (int mask = 1; mask < (1 << M); ++mask) {
            int bits = 0;
            long long l = 1;
            for (int i = 0; i < M; ++i) {
                if (mask & (1 << i)) {
                    bits++;
                    l = l / gcd(l, S[i]) * S[i];
                    if (l > N) break;
                }
            }
            if (l <= N) {
                if (bits % 2 == 1) {
                    ans -= N / l;
                } else {
                    ans += N / l;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
