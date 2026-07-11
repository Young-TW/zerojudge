#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

void fmt(vector<int>& a, int n) {
    for (int i = 0; i < n; ++i) {
        int bit = 1 << i;
        for (int j = 0; j < (1 << n); j += bit << 1) {
            for (int t = 0; t < bit; ++t) {
                a[j + bit + t] += a[j + t];
                if (a[j + bit + t] >= MOD) a[j + bit + t] -= MOD;
            }
        }
    }
}

void ifmt(vector<int>& a, int n) {
    for (int i = 0; i < n; ++i) {
        int bit = 1 << i;
        for (int j = 0; j < (1 << n); j += bit << 1) {
            for (int t = 0; t < bit; ++t) {
                a[j + bit + t] -= a[j + t];
                if (a[j + bit + t] < 0) a[j + bit + t] += MOD;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        int n = 0;
        while ((1 << n) < N) n++;
        
        vector<int> a(N), b(N);
        for (int i = 0; i < N; ++i) cin >> a[i];
        for (int i = 0; i < N; ++i) cin >> b[i];
        
        vector<vector<int>> A(n + 1, vector<int>(N, 0));
        vector<vector<int>> B(n + 1, vector<int>(N, 0));
        
        for (int i = 0; i < N; ++i) {
            int pc = __builtin_popcount(i);
            A[pc][i] = a[i];
            B[pc][i] = b[i];
        }
        
        for (int i = 0; i <= n; ++i) {
            fmt(A[i], n);
            fmt(B[i], n);
        }
        
        vector<vector<int>> C(n + 1, vector<int>(N, 0));
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (int k = 0; k < N; ++k) {
                    C[i][k] = (C[i][k] + (long long)A[j][k] * B[i - j][k]) % MOD;
                }
            }
        }
        
        for (int i = 0; i <= n; ++i) {
            ifmt(C[i], n);
        }
        
        for (int i = 0; i < N; ++i) {
            cout << C[__builtin_popcount(i)][i] << (i == N - 1 ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
