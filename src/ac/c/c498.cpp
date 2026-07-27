#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;
using int64 = long long;
using i128 = __int128_t;

int64 gcd_ll(int64 a, int64 b) {
    while (b) { int64 t = a % b; a = b; b = t; }
    return a;
}

void exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) { x = 1; y = 0; return; }
    int64 x1, y1;
    exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
}

int64 modInv(int64 a, int64 mod) {
    int64 x, y;
    exgcd(a, mod, x, y);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

int cntInRange(const vector<int>& v, int l, int r) {
    if (l > r) return 0;
    auto it1 = lower_bound(v.begin(), v.end(), l);
    auto it2 = upper_bound(v.begin(), v.end(), r);
    return int(it2 - it1);
}

void print_i128(i128 x) {
    if (x == 0) { cout << '0'; return; }
    string s;
    while (x > 0) { s.push_back(char('0' + int(x % 10))); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string A, B;
    int64 T;
    while (cin >> A >> B >> T) {
        int64 n = A.size();
        int64 m = B.size();
        int64 g = gcd_ll(n, m);
        int64 n1 = n / g;
        int64 m1 = m / g;

        vector<array<int64, 26>> cntA(g), cntB(g);
        for (int i = 0; i < g; ++i) {
            cntA[i].fill(0);
            cntB[i].fill(0);
        }

        vector<vector<int>> Acls(g, vector<int>(n1));
        for (int64 i = 0; i < n; ++i) {
            int k = int(i % g);
            int u = int(i / g);
            int c = A[i] - 'a';
            cntA[k][c]++;
            Acls[k][u] = c;
        }

        vector<vector<int>> Bcls(g, vector<int>(m1));
        for (int64 i = 0; i < m; ++i) {
            int k = int(i % g);
            int v = int(i / g);
            int d = B[i] - 'a';
            cntB[k][d]++;
            Bcls[k][v] = d;
        }

        i128 sum_one = 0;
        for (int k = 0; k < g; ++k) {
            for (int c = 0; c < 26; ++c) {
                if (!cntA[k][c]) continue;
                for (int d = 0; d < 26; ++d) {
                    if (!cntB[k][d]) continue;
                    i128 add = (i128)cntA[k][c] * (i128)cntB[k][d];
                    add *= (i128)(26 - abs(c - d));
                    sum_one += add;
                }
            }
        }

        int64 L = n1 * m;
        int64 q = T / L;
        int64 R = T % L;

        i128 answer = (i128)q * sum_one;

        if (R > 0) {
            bool simpleM1 = (m1 == 1);
            int64 inv = 0;
            if (!simpleM1) {
                inv = modInv(n1 % m1, m1);
            }

            vector<array<vector<int>, 26>> Svec(g);
            if (!simpleM1) {
                for (int k = 0; k < g; ++k) {
                    for (int d = 0; d < 26; ++d) Svec[k][d].clear();
                    for (int v = 0; v < (int)m1; ++v) {
                        int d = Bcls[k][v];
                        int s0 = int((1LL * v * inv) % m1);
                        Svec[k][d].push_back(s0);
                    }
                    for (int d = 0; d < 26; ++d) {
                        sort(Svec[k][d].begin(), Svec[k][d].end());
                    }
                }
            }

            for (int k = 0; k < g; ++k) {
                if (R <= k) continue;
                int64 Rk = (R - 1 - k) / g + 1;

                for (int u = 0; u < (int)n1; ++u) {
                    if (u >= Rk) break;
                    int c = Acls[k][u];
                    int64 limit = (Rk - 1 - u) / n1;
                    int64 total_s = limit + 1;
                    int64 full = total_s / m1;
                    int rem = int(total_s % m1);

                    int offset = 0;
                    if (!simpleM1) {
                        offset = int((1LL * u * inv) % m1);
                    }

                    for (int d = 0; d < 26; ++d) {
                        if (!cntB[k][d]) continue;
                        int64 cnt = full * cntB[k][d];
                        if (rem) {
                            if (!simpleM1) {
                                int l = offset;
                                int r = offset + rem - 1;
                                if (r < (int)m1) {
                                    cnt += cntInRange(Svec[k][d], l, r);
                                } else {
                                    cnt += cntInRange(Svec[k][d], l, (int)m1 - 1);
                                    cnt += cntInRange(Svec[k][d], 0, r - (int)m1);
                                }
                            } else {
                                cnt += cntB[k][d];
                            }
                        }
                        answer += (i128)cnt * (i128)(26 - abs(c - d));
                    }
                }
            }
        }

        print_i128(answer);
        cout << '\n';
    }
    return 0;
}
