#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    long long m[3][3];
    Matrix() {
        memset(m, 0, sizeof(m));
    }
    Matrix operator*(const Matrix& o) const {
        Matrix res;
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                if (m[i][k]) {
                    for (int j = 0; j < 3; ++j) {
                        res.m[i][j] = (res.m[i][j] + m[i][k] * o.m[k][j]) % MOD;
                    }
                }
            }
        }
        return res;
    }
};

vector<long long> mul(const Matrix& mat, const vector<long long>& v) {
    vector<long long> res(3, 0);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            res[i] = (res[i] + mat.m[i][j] * v[j]) % MOD;
        }
    }
    return res;
}

Matrix power(Matrix base, long long exp) {
    Matrix res;
    for (int i = 0; i < 3; ++i) res.m[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N, M;
    while (cin >> N >> M) {
        Matrix M_good, M_bad;
        M_good.m[0][0] = 1; M_good.m[0][1] = 1; M_good.m[0][2] = 1;
        M_good.m[1][0] = 1; M_good.m[1][1] = 0; M_good.m[1][2] = 0;
        M_good.m[2][0] = 0; M_good.m[2][1] = 1; M_good.m[2][2] = 0;

        M_bad.m[0][0] = 0; M_bad.m[0][1] = 0; M_bad.m[0][2] = 0;
        M_bad.m[1][0] = 1; M_bad.m[1][1] = 0; M_bad.m[1][2] = 0;
        M_bad.m[2][0] = 0; M_bad.m[2][1] = 1; M_bad.m[2][2] = 0;

        map<long long, Matrix> bad_map;
        Matrix identity;
        for (int i = 0; i < 3; ++i) identity.m[i][i] = 1;
        bad_map[2] = identity;

        bool bad1 = false, bad2 = false;

        for (long long i = 0; i < M; ++i) {
            long long x, k;
            cin >> x >> k;
            if (x == 1) {
                if (k == 1) {
                    bad1 = true;
                } else if (k == 2) {
                    bad2 = true;
                } else {
                    if (bad_map.find(k) == bad_map.end()) {
                        auto it = bad_map.lower_bound(k);
                        --it;
                        long long prev = it->first;
                        Matrix prev_mat = it->second;
                        Matrix good_pow = power(M_good, k - prev - 1);
                        Matrix cur_mat = M_bad * good_pow * prev_mat;
                        bad_map[k] = cur_mat;
                    }
                }
            } else {
                long long ans;
                if (k == 1) {
                    ans = bad1 ? 0 : 1;
                } else if (k == 2) {
                    ans = bad2 ? 0 : 2;
                } else {
                    auto it = bad_map.upper_bound(k);
                    --it;
                    long long prev = it->first;
                    if (prev == k) {
                        ans = 0;
                    } else {
                        Matrix prev_mat = it->second;
                        Matrix good_pow = power(M_good, k - prev);
                        Matrix cur_mat = good_pow * prev_mat;
                        vector<long long> V(3);
                        V[0] = bad2 ? 0 : 2;
                        V[1] = bad1 ? 0 : 1;
                        V[2] = 1;
                        vector<long long> res = mul(cur_mat, V);
                        ans = res[0];
                    }
                }
                cout << ans << "\n";
            }
        }
    }

    return 0;
}
