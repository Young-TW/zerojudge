#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Interval = pair<ll, ll>;

static vector<Interval> merge_intervals(vector<Interval> &v) {
    if (v.empty()) return {};
    sort(v.begin(), v.end(),
         [](const Interval &a, const Interval &b) {
             if (a.first != b.first) return a.first < b.first;
             return a.second < b.second;
         });
    vector<Interval> res;
    for (auto &p : v) {
        if (res.empty() || p.first > res.back().second) {
            res.push_back(p);
        } else {
            if (p.second > res.back().second)
                res.back().second = p.second;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    if (!(cin >> N)) return 0;          // no input
    vector<Interval> add, rem;
    add.reserve(N);
    rem.reserve(N);
    for (long long i = 0; i < N; ++i) {
        int ty;
        ll s, e;
        cin >> ty >> s >> e;
        if (ty == 1) add.emplace_back(s, e);
        else if (ty == 2) rem.emplace_back(s, e);
    }

    vector<Interval> A = merge_intervals(add);
    vector<Interval> R = merge_intervals(rem);

    vector<Interval> ans;
    size_t j = 0;                       // index in R
    for (size_t i = 0; i < A.size(); ++i) {
        ll curL = A[i].first;
        ll curR = A[i].second;

        while (j < R.size() && R[j].second <= curL) ++j;   // skip left of A[i]

        size_t k = j;
        while (k < R.size() && R[k].first < curR) {
            if (R[k].first > curL) {
                ll right = min(R[k].first, curR);
                if (curL < right) ans.emplace_back(curL, right);
            }
            curL = max(curL, R[k].second);
            if (curL >= curR) break;
            ++k;
        }
        if (curL < curR) ans.emplace_back(curL, curR);
        j = k;                         // next A starts not earlier than k
    }

    cout << ans.size() << '\n';
    for (auto &p : ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
