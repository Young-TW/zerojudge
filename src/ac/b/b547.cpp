#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Spec {
    char f, s;
};

struct Constraint {
    int type;       // 1: full row, 2: adjacent pair, 3: leftmost+rightmost
    Spec specs[3];
};

bool matchSpec(const Spec& sp, char f, char s) {
    if (sp.f != '?' && sp.f != f) return false;
    if (sp.s != '?' && sp.s != s) return false;
    return true;
}

bool matchRow(const Constraint& con, char f0, char s0, char f1, char s1, char f2, char s2) {
    if (con.type == 1) {
        return matchSpec(con.specs[0], f0, s0) &&
               matchSpec(con.specs[1], f1, s1) &&
               matchSpec(con.specs[2], f2, s2);
    } else if (con.type == 2) {
        return (matchSpec(con.specs[0], f0, s0) && matchSpec(con.specs[1], f1, s1)) ||
               (matchSpec(con.specs[0], f1, s1) && matchSpec(con.specs[1], f2, s2));
    } else {
        return matchSpec(con.specs[0], f0, s0) && matchSpec(con.specs[2], f2, s2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const char flav[3] = {'P', 'B', 'Y'};
    const char shap[3] = {'S', 'C', 'T'};

    int N;
    while (cin >> N) {
        vector<Constraint> constraints;
        constraints.reserve(N);

        for (int i = 0; i < N; ++i) {
            int K; cin >> K;
            Spec v[3];
            for (int j = 0; j < K; ++j) {
                cin >> v[j].f >> v[j].s;
            }
            Constraint con;
            if (K == 3) {
                if (v[1].f == '?' && v[1].s == '?') {
                    con.type = 3;
                    con.specs[0] = v[0];
                    con.specs[2] = v[2];
                } else {
                    con.type = 1;
                    con.specs[0] = v[0];
                    con.specs[1] = v[1];
                    con.specs[2] = v[2];
                }
            } else {
                con.type = 2;
                con.specs[0] = v[0];
                con.specs[1] = v[1];
            }
            constraints.push_back(con);
        }

        vector<int> perm(9);
        iota(perm.begin(), perm.end(), 0);

        long long answer = 0;

        do {
            char f[9], s[9];
            for (int i = 0; i < 9; ++i) {
                f[i] = flav[perm[i] / 3];
                s[i] = shap[perm[i] % 3];
            }

            bool okAll = true;
            for (int ci = 0; ci < (int)constraints.size(); ++ci) {
                const Constraint& con = constraints[ci];
                bool satisfied = false;
                for (int r = 0; r < 3 && !satisfied; ++r) {
                    int b = r * 3;
                    if (matchRow(con, f[b], s[b], f[b+1], s[b+1], f[b+2], s[b+2])) {
                        satisfied = true;
                    }
                }
                if (!satisfied) {
                    okAll = false;
                    break;
                }
            }
            if (okAll) ++answer;
        } while (next_permutation(perm.begin(), perm.end()));

        cout << answer << '\n';
    }
    return 0;
}
