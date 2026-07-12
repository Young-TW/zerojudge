#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
const int LOG = 20;

int sopf[MAXN];
int primes[MAXN];
int prime_cnt = 0;

unsigned char lsopf[MAXN];
unsigned char sparse_table[MAXN][LOG];
int lg2[MAXN];

void precompute() {
    for (int i = 2; i < MAXN; ++i) {
        if (sopf[i] == 0) {
            sopf[i] = i;
            primes[prime_cnt++] = i;
        }
        for (int j = 0; j < prime_cnt && primes[j] * i < MAXN; ++j) {
            int p = primes[j];
            sopf[p * i] = sopf[i] + p;
            if (i % p == 0) break;
        }
    }

    for (int i = 2; i < MAXN; ++i) {
        if (sopf[i] == i) {
            lsopf[i] = 1;
        } else {
            lsopf[i] = lsopf[sopf[i]] + 1;
        }
    }

    for (int i = 2; i < MAXN; ++i) {
        sparse_table[i][0] = lsopf[i];
    }
    for (int j = 1; j < LOG; ++j) {
        for (int i = 2; i + (1 << j) - 1 < MAXN; ++i) {
            int val1 = sparse_table[i][j - 1];
            int val2 = sparse_table[i + (1 << (j - 1))][j - 1];
            sparse_table[i][j] = (val1 > val2) ? val1 : val2;
        }
    }

    lg2[1] = 0;
    for (int i = 2; i < MAXN; ++i) {
        lg2[i] = lg2[i / 2] + 1;
    }
}

int query(int l, int r) {
    if (l > r) std::swap(l, r);
    int k = lg2[r - l + 1];
    int val1 = sparse_table[l][k];
    int val2 = sparse_table[r - (1 << k) + 1][k];
    return (val1 > val2) ? val1 : val2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int T;
    while (cin >> T) {
        for (int c = 1; c <= T; ++c) {
            int n, m;
            cin >> n >> m;
            cout << "Case #" << c << ":\n";
            cout << query(n, m) << "\n";
        }
    }
    return 0;
}
