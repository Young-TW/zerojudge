#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll f;          // F[i] = pref[i] - a*i
    int g;         // compressed G[i]
    int idx;       // original index i
};

struct BIT {
    int n;
    vector<int> bit;
    BIT(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 2, 0); }
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    long long sum(int idx) const {
        long long s = 0;
        for (; idx > 0; idx -= idx & -idx) s += bit[idx];
        return s;
    }
};

vector<Node> nodes;
BIT bit;
long long answer = 0;
int Gmax;                     // number of distinct compressed G values

void cdq(int L, int R) {
    if (L >= R) return;
    int mid = (L + R) >> 1;
    cdq(L, mid);
    cdq(mid + 1, R);

    // copy left and right parts
    vector<Node> left(nodes.begin() + L, nodes.begin() + mid + 1);
    vector<Node> right(nodes.begin() + mid + 1, nodes.begin() + R + 1);

    auto cmpF = [](const Node& a, const Node& b) {
        if (a.f != b.f) return a.f < b.f;
        return a.idx < b.idx;
    };
    sort(left.begin(), left.end(), cmpF);
    sort(right.begin(), right.end(), cmpF);

    size_t p = 0;
    for (const Node& rp : right) {
        while (p < left.size() && left[p].f <= rp.f) {
            bit.add(left[p].g, 1);
            ++p;
        }
        long long cnt = bit.sum(Gmax) - bit.sum(rp.g - 1); // G[l] >= G[r]
        answer += cnt;
    }
    // clean BIT
    for (size_t i = 0; i < p; ++i) bit.add(left[i].g, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long a, b;
    while (cin >> n >> a >> b) {
        vector<long long> pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            long long x; cin >> x;
            pref[i] = pref[i - 1] + x;
        }

        nodes.assign(n + 1, Node());
        vector<long long> allG;
        allG.reserve(n + 1);
        for (int i = 0; i <= n; ++i) {
            ll f = pref[i] - a * (ll)i;
            ll g = pref[i] - b * (ll)i;
            nodes[i].f = f;
            nodes[i].idx = i;
            allG.push_back(g);
        }

        // coordinate compression of G
        sort(allG.begin(), allG.end());
        allG.erase(unique(allG.begin(), allG.end()), allG.end());
        Gmax = (int)allG.size();
        for (int i = 0; i <= n; ++i) {
            ll g_raw = pref[i] - b * (ll)i;
            int pos = lower_bound(allG.begin(), allG.end(), g_raw) - allG.begin() + 1;
            nodes[i].g = pos;
        }

        bit.init(Gmax);
        answer = 0;
        cdq(0, n);
        cout << answer << '\n';
    }
    return 0;
}
