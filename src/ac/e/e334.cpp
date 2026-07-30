#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int w;
};

int n, m;
vector<vector<Edge>> adj;
vector<int> parent;
vector<int> order;
vector<long long> up;
int cnt;

bool enough(long long lim) {
    cnt = 0;
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        multiset<long long> ms;
        for (size_t j = 0; j < adj[u].size(); ++j) {
            int v = adj[u][j].to;
            if (v == parent[u]) continue;
            long long val = up[v] + (long long)adj[u][j].w;
            if (val >= lim) {
                ++cnt;
                if (cnt >= m) return true;
            } else {
                ms.insert(val);
            }
        }
        long long best = 0;
        while (!ms.empty()) {
            long long t = *ms.begin();
            ms.erase(ms.begin());
            multiset<long long>::iterator it = ms.lower_bound(lim - t);
            if (it != ms.end()) {
                ms.erase(it);
                ++cnt;
                if (cnt >= m) return true;
            } else {
                best = t;
            }
        }
        up[u] = best;
    }
    return cnt >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool firstOut = true;
    while (cin >> n >> m) {
        if (!firstOut) cout << '\n';
        firstOut = false;

        adj.assign(n + 1, vector<Edge>());
        long long sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            int a, b, l;
            cin >> a >> b >> l;
            adj[a].push_back(Edge{b, l});
            adj[b].push_back(Edge{a, l});
            sum += l;
        }

        parent.assign(n + 1, 0);
        up.assign(n + 1, 0);
        order.clear();
        order.reserve(n);

        vector<int> st;
        st.reserve(n);
        st.push_back(1);
        parent[1] = -1;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (size_t j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j].to;
                if (v == parent[u]) continue;
                parent[v] = u;
                st.push_back(v);
            }
        }

        long long lo = 0, hi = sum / m;
        while (lo < hi) {
            long long mid = lo + (hi - lo + 1) / 2;
            if (enough(mid)) lo = mid;
            else hi = mid - 1;
        }
        cout << lo << '\n';
    }
    return 0;
}
