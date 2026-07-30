#include <bits/stdc++.h>
using namespace std;

struct Hit {
    string name;   // printed representation
    int pts;       // points contributed
    int mul;       // multiplier: 0 (MISS), 1, 2, 3
    bool isDouble; // true for Dn and D-BULL
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long s, k;
    while (cin >> s >> k) {
        vector<Hit> hits;

        // singles 1..20
        for (int n = 1; n <= 20; ++n)
            hits.push_back({to_string(n), n, 1, false});

        // doubles 1..20
        for (int n = 1; n <= 20; ++n)
            hits.push_back({"D" + to_string(n), 2 * n, 2, true});

        // triples 1..20
        for (int n = 1; n <= 20; ++n)
            hits.push_back({"T" + to_string(n), 3 * n, 3, false});

        // bull and double bull
        hits.push_back({"BULL", 25, 1, false});
        hits.push_back({"D-BULL", 50, 2, true});

        // miss
        hits.push_back({"MISS", 0, 0, false});

        // indices of double hits (possible final darts)
        vector<int> doubleIdx;
        for (int i = 0; i < (int)hits.size(); ++i)
            if (hits[i].isDouble) doubleIdx.push_back(i);

        using Way = vector<int>;
        vector<Way> ways;

        // length 1
        for (int d : doubleIdx) {
            if (hits[d].pts == s) ways.push_back({d});
        }

        // length 2
        for (int a = 0; a < (int)hits.size(); ++a) {
            for (int d : doubleIdx) {
                if ((long long)hits[a].pts + hits[d].pts == s)
                    ways.push_back({a, d});
            }
        }

        // length 3
        for (int a = 0; a < (int)hits.size(); ++a) {
            for (int b = 0; b < (int)hits.size(); ++b) {
                long long sum2 = (long long)hits[a].pts + hits[b].pts;
                if (sum2 > s) continue;
                for (int d : doubleIdx) {
                    if (sum2 + hits[d].pts == s)
                        ways.push_back({a, b, d});
                }
            }
        }

        // comparator according to the problem statement
        auto cmp = [&](const Way &A, const Way &B) {
            if (A.size() != B.size()) return A.size() < B.size(); // fewer darts better
            for (size_t i = 0; i < A.size(); ++i) {
                const Hit &ha = hits[A[i]];
                const Hit &hb = hits[B[i]];
                if (ha.pts != hb.pts) return ha.pts > hb.pts; // larger points first
                if (ha.mul != hb.mul) return ha.mul > hb.mul; // larger multiplier first
            }
            return false; // equal
        };

        sort(ways.begin(), ways.end(), cmp);

        if (k < 1 || (size_t)k > ways.size()) {
            cout << "No Way!\n";
        } else {
            const Way &ans = ways[k - 1];
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i) cout << ' ';
                cout << hits[ans[i]].name;
            }
            cout << '\n';
        }
    }
    return 0;
}
