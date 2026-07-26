#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        unordered_map<int, int> id_of;          // value -> id
        vector<int> value;                      // id -> value
        vector<array<pair<int,int>,2>> pos;     // id -> two positions

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x; cin >> x;
                grid[i][j] = x;
                auto it = id_of.find(x);
                if (it == id_of.end()) {
                    int id = (int)value.size();
                    id_of[x] = id;
                    value.push_back(x);
                    pos.push_back({make_pair(-1,-1), make_pair(-1,-1)});
                    pos[id][0] = make_pair(i, j);
                } else {
                    int id = it->second;
                    pos[id][1] = make_pair(i, j);
                }
            }
        }

        int K = (int)value.size();
        vector<char> aligned(K, 0);
        for (int id = 0; id < K; ++id) {
            int r1 = pos[id][0].first, c1 = pos[id][0].second;
            int r2 = pos[id][1].first, c2 = pos[id][1].second;
            if (r1 == r2 || c1 == c2) aligned[id] = 1;
        }

        vector<vector<int>> adj(K);
        vector<int> indeg(K, 0);

        // build edges: for every aligned pair B, all cells between its two positions
        for (int b = 0; b < K; ++b) if (aligned[b]) {
            int r1 = pos[b][0].first, c1 = pos[b][0].second;
            int r2 = pos[b][1].first, c2 = pos[b][1].second;
            if (r1 == r2) { // same row
                int row = r1;
                int left = min(c1, c2), right = max(c1, c2);
                for (int c = left + 1; c < right; ++c) {
                    int val = grid[row][c];
                    int a = id_of[val];
                    adj[a].push_back(b);
                    ++indeg[b];
                }
            } else { // same column
                int col = c1;
                int top = min(r1, r2), bottom = max(r1, r2);
                for (int r = top + 1; r < bottom; ++r) {
                    int val = grid[r][col];
                    int a = id_of[val];
                    adj[a].push_back(b);
                    ++indeg[b];
                }
            }
        }

        // Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < K; ++i)
            if (aligned[i] && indeg[i] == 0) q.push(i);

        long long answer = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            answer += value[u];
            for (int v : adj[u]) {
                if (--indeg[v] == 0 && aligned[v])
                    q.push(v);
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
