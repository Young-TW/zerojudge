#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<long long> cost(n+1);
        for (int i = 1; i <= n; i++) cin >> cost[i];
        
        vector<vector<pair<int,long long> > > deps(n+1);
        vector<int> indeg(n+1, 0);
        vector<vector<int> > g(n+1);
        
        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            indeg[i] = k;
            for (int j = 0; j < k; j++) {
                int a; long long b;
                cin >> a >> b;
                deps[i].push_back(make_pair(a, b));
                g[a].push_back(i);
            }
        }
        
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) q.push(i);
        }
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (size_t j = 0; j < deps[u].size(); j++) {
                cost[u] += deps[u][j].second * cost[deps[u][j].first];
            }
            for (size_t j = 0; j < g[u].size(); j++) {
                if (--indeg[g[u][j]] == 0) q.push(g[u][j]);
            }
        }
        
        for (int i = 1; i <= n; i++) {
            cout << cost[i] << "\n";
        }
    }
    return 0;
}
