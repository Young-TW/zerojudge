#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

void fwt(vector<long long>& a, int n, bool inv) {
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; ++j) {
                if (!inv) {
                    a[i + j] = (a[i + j] + a[i + j + len]) % MOD;
                } else {
                    a[i + j] = (a[i + j] - a[i + j + len] + MOD) % MOD;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<long long> a(N), b(N);
        for (int i = 0; i < N; ++i) cin >> a[i];
        for (int i = 0; i < N; ++i) cin >> b[i];
        
        fwt(a, N, false);
        fwt(b, N, false);
        
        for (int i = 0; i < N; ++i) {
            a[i] = (a[i] * b[i]) % MOD;
        }
        
        fwt(a, N, true);
        
        for (int i = 0; i < N; ++i) {
            cout << a[i] << (i == N - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
