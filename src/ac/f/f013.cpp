#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
const int MAX_N = 30;
const int MAX_BIT = 60;                 // enough for k ≤ 2^50

using Matrix = vector<vector<long long>>;

/* matrix multiplication (size n) */
static Matrix mulMat(const Matrix& A, const Matrix& B, int n) {
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) if (A[i][k]) {
            long long aik = A[i][k];
            for (int j = 0; j < n; ++j) {
                C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

/* matrix (n×n) times vector (n) */
static vector<long long> mulMatVec(const Matrix& A,
                                   const vector<long long>& v,
                                   int n) {
    vector<long long> res(n, 0);
    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += A[i][j] * v[j];
            if (sum >= (1LL<<62)) sum %= MOD;   // avoid overflow
        }
        res[i] = sum % MOD;
    }
    return res;
}

/* pre‑computed powers for every n */
static vector<Matrix> pre[MAX_N + 1];   // pre[n][bit]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* ---------- pre‑computation for all n = 2 … 30 ---------- */
    for (int n = 2; n <= MAX_N; ++n) {
        pre[n].resize(MAX_BIT);
        Matrix base(n, vector<long long>(n, 0));
        // first row = 1
        for (int j = 0; j < n; ++j) base[0][j] = 1;
        // sub‑diagonal = 1
        for (int i = 1; i < n; ++i) base[i][i-1] = 1;

        pre[n][0] = base;
        for (int b = 1; b < MAX_BIT; ++b) {
            pre[n][b] = mulMat(pre[n][b-1], pre[n][b-1], n);
        }
    }

    /* ------------------- answer queries ------------------- */
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        unsigned long long k;          // k up to 2^50 fits in 64‑bit
        cin >> n >> k;

        if (k <= (unsigned long long)n) {
            cout << 1 << '\n';
            continue;
        }

        unsigned long long e = k - n;          // exponent
        vector<long long> vec(n, 1);            // S(n) = all 1

        int bit = 0;
        while (e) {
            if (e & 1ULL) {
                vec = mulMatVec(pre[n][bit], vec, n);
            }
            e >>= 1ULL;
            ++bit;
        }
        cout << vec[0] % MOD << '\n';
    }
    return 0;
}
