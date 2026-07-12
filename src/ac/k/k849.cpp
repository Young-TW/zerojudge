#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <utility>

using namespace std;

struct Edge {
    int to;
    int id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<pair<int, int>> edges(n);
        vector<int> vals;
        for (int i = 0; i < n; ++i) {
            cin >> edges[i].first >> edges[i].second;
            vals.push_back(edges[i].first);
            vals.push_back(edges[i].second);
        }

        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();
        map<int, int> val_to_id;
        for (int i = 0; i < m; ++i) {
            val_to_id[vals[i]] = i;
        }

        int minus_one_id = -1;
        if (val_to_id.count(-1)) {
            minus_one_id = val_to_id[-1];
        }

        vector<vector<Edge>> adj(m);
        vector<int> deg(m, 0);
        for (int i = 0; i < n; ++i) {
            int u = val_to_id[edges[i].first];
            int v = val_to_id[edges[i].second];
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            deg[u]++;
            deg[v]++;
        }

        int start = -1;
        for (int i = 0; i < m; ++i) {
            if (deg[i] % 2 == 1 && i != minus_one_id) {
                start = i;
                break;
            }
        }

        if (start == -1) {
            for (int i = 0; i < m; ++i) {
                if (!adj[i].empty()) {
                    start = i;
                    break;
                }
            }
        }

        vector<bool> vis(n, false);
        stack<int> st;
        st.push(start);
        vector<int> path;

        while (!st.empty()) {
            int u = st.top();
            bool found = false;
            while (!adj[u].empty()) {
                Edge e = adj[u].back();
                adj[u].pop_back();
                if (!vis[e.id]) {
                    vis[e.id] = true;
                    st.push(e.to);
                    found = true;
                    break;
                }
            }
            if (!found) {
                path.push_back(u);
                st.pop();
            }
        }

        bool first = true;
        for (int i = path.size() - 1; i >= 0; --i) {
            if (path[i] != minus_one_id) {
                if (!first) cout << " ";
                cout << vals[path[i]];
                first = false;
            }
        }
        cout << "\n";
    }

    return 0;
}
