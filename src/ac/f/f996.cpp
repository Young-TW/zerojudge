#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <algorithm>

using namespace std;

const unsigned long long MOD = 1000000007;

unsigned long long M[16][61][15][15];

template <int N>
void multiply(unsigned long long V[], unsigned long long next_V[], unsigned long long mat[][15]) {
    for (int j = 0; j < N; ++j) {
        unsigned long long sum = 0;
        unsigned long long *row = mat[j];
        for (int l = 0; l < N; ++l) {
            sum += row[l] * V[l];
        }
        next_V[j] = sum % MOD;
    }
}

void precompute() {
    for (int n = 2; n <= 15; ++n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                M[n][0][i][j] = 0;
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            M[n][0][i][i + 1] = 1;
        }
        for (int j = 0; j < n; ++j) {
            M[n][0][n - 1][j] = 1;
        }

        for (int p = 1; p <= 60; ++p) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    unsigned long long sum = 0;
                    for (int l = 0; l < n; ++l) {
                        sum += M[n][p - 1][i][l] * M[n][p - 1][l][j];
                    }
                    M[n][p][i][j] = sum % MOD;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    if (!(cin >> t)) return 0;
    long long n, k;
    while (cin >> n >> k) {
        if (k <= n) {
            cout << 1 << "\n";
            continue;
        }
        unsigned long long V[15];
        unsigned long long next_V[15];
        unsigned long long *curr = V;
        unsigned long long *next = next_V;
        for (int i = 0; i < n; ++i) curr[i] = 1;
        long long diff = k - n;
        for (int i = 0; i <= 60; ++i) {
            if (!((diff >> i) & 1)) continue;
            switch (n) {
                case 2: multiply<2>(curr, next, M[n][i]); break;
                case 3: multiply<3>(curr, next, M[n][i]); break;
                case 4: multiply<4>(curr, next, M[n][i]); break;
                case 5: multiply<5>(curr, next, M[n][i]); break;
                case 6: multiply<6>(curr, next, M[n][i]); break;
                case 7: multiply<7>(curr, next, M[n][i]); break;
                case 8: multiply<8>(curr, next, M[n][i]); break;
                case 9: multiply<9>(curr, next, M[n][i]); break;
                case 10: multiply<10>(curr, next, M[n][i]); break;
                case 11: multiply<11>(curr, next, M[n][i]); break;
                case 12: multiply<12>(curr, next, M[n][i]); break;
                case 13: multiply<13>(curr, next, M[n][i]); break;
                case 14: multiply<14>(curr, next, M[n][i]); break;
                case 15: multiply<15>(curr, next, M[n][i]); break;
            }
            swap(curr, next);
        }
        cout << curr[n - 1] << "\n";
    }
    return 0;
}
