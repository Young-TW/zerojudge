#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

void FWT_OR(vector<long long>& a, bool inv) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; ++j) {
                if (!inv) {
                    a[i + j + len] = (a[i + j + len] + a[i + j]) % MOD;
                } else {
                    a[i + j + len] = (a[i + j + len] - a[i + j] + MOD) % MOD;
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
        
        FWT_OR(a, false);
        FWT_OR(b, false);
        
        for (int i = 0; i < N; ++i) {
            a[i] = (a[i] * b[i]) % MOD;
        }
        
        FWT_OR(a, true);
        
        for (int i = 0; i < N; ++i) {
            cout << a[i] << (i == N - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
