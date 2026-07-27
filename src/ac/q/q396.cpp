#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000;

bool lessBits(const vector<char> &A, const vector<char> &B, int n) {
    for (int i = n; i >= 1; --i) {
        if (A[i] != B[i]) return A[i] < B[i];   // 0 < 1
    }
    return false; // equal
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> pos(n + 1, -1);
        for (int peg = 0; peg < 3; ++peg) {
            int m; cin >> m;
            for (int j = 0; j < m; ++j) {
                int x; cin >> x;
                pos[x] = peg;
            }
        }

        // powers of two modulo MOD
        vector<int> pow2mod(n);
        if (n > 0) {
            pow2mod[0] = 1 % MOD;
            for (int i = 1; i < n; ++i) {
                pow2mod[i] = (pow2mod[i - 1] * 2) % MOD;
            }
        }

        // bits[t][i] : i-th disk (1‑based) contributes 2^{i-1}
        vector< vector<char> > bits(3, vector<char>(n + 1, 0));
        int modAns[3] = {0, 0, 0};

        for (int t = 0; t < 3; ++t) {
            int cur = t;
            int curMod = 0;
            for (int i = n; i >= 1; --i) {
                if (pos[i] == cur) continue;
                bits[t][i] = 1;
                curMod += pow2mod[i - 1];
                if (curMod >= MOD) curMod -= MOD;
                cur = 3 - cur - pos[i]; // the third peg
            }
            modAns[t] = curMod;
        }

        // choose the best target peg
        int best = 0;
        for (int t = 1; t < 3; ++t) {
            if (lessBits(bits[t], bits[best], n))
                best = t;
        }

        // decide whether the exact answer exceeds MOD
        bool large = false;
        unsigned long long exact = 0;
        for (int i = 1; i <= n; ++i) {
            if (!bits[best][i]) continue;
            if (i - 1 >= 20) {
                large = true;
                continue;
            }
            exact += (1ULL << (i - 1));
            if (exact > (unsigned long long)MOD) large = true;
        }

        if (!large) {
            cout << exact << '\n';
        } else {
            cout << modAns[best] << '\n';
        }
    }
    return 0;
}
