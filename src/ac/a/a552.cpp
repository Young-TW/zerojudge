#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> adj(n);
        vector<int> indeg(n, 0);
        for (int k = 0; k < m; k++) {
            int i, j;
            cin >> i >> j;
            adj[i].push_back(j);
            indeg[j]++;
        }
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int v = 0; v < n; v++) {
            if (indeg[v] == 0) pq.push(v);
        }
        vector<int> order;
        order.reserve(n);
        while (!pq.empty()) {
            int v = pq.top(); pq.pop();
            order.push_back(v);
            for (int u : adj[v]) {
                if (--indeg[u] == 0) pq.push(u);
            }
        }
        for (int i = 0; i < (int)order.size(); i++) {
            cout << order[i];
            if (i + 1 < (int)order.size()) cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
