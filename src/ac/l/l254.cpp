#include <iostream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N;
    while (cin >> N) {
        vector<vector<pair<int, ll>>> adj(N + 1);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        vector<int> parent(N + 1, 0);
        vector<int> order;
        stack<int> st;
        st.push(1);
        parent[1] = 0;
        while (!st.empty()) {
            int u = st.top(); st.pop();
            order.push_back(u);
            for (auto &p : adj[u]) {
                int v = p.first;
                if (v != parent[u]) {
                    parent[v] = u;
                    st.push(v);
                }
            }
        }
        
        vector<ll> sg(N + 1, 0);
        for (int i = order.size() - 1; i >= 0; --i) {
            int u = order[i];
            int cnt0 = 0;
            ll w0 = 0;
            for (auto &p : adj[u]) {
                int v = p.first;
                if (v == parent[u]) continue;
                if (sg[v] == 0) {
                    cnt0++;
                    w0 = p.second;
                    if (cnt0 >= 2) break;
                }
            }
            if (cnt0 == 0) sg[u] = 0;
            else if (cnt0 == 1) sg[u] = w0;
            else sg[u] = 1;
        }
        
        cout << (sg[1] != 0 ? "First" : "Second") << "\n";
    }
    return 0;
}
