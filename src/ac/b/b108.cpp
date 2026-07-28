#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

pair<int, int> bfs(int src, const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    vector<int> q;
    dist[src] = 0;
    q.push_back(src);
    int far = src, farDist = 0;
    for (int i = 0; i < q.size(); ++i) {
        int v = q[i];
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                if (dist[u] > farDist) {
                    farDist = dist[u];
                    far = u;
                }
                q.push_back(u);
            }
        }
    }
    return {far, farDist};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        int N;
        {
            stringstream ss(line);
            ss >> N;
        }
        vector<vector<int>> adj(N);
        for (int i = 0; i < N; ++i) {
            string row;
            if (!getline(cin, row)) {
                row = "";
            }
            stringstream ss(row);
            int x;
            while (ss >> x) {
                if (x == -1) break;
                adj[i].push_back(x);
                adj[x].push_back(i);
            }
        }
        if (N == 0) {
            cout << 0 << '\n';
            continue;
        }
        int A = bfs(0, adj).first;
        int diameter = bfs(A, adj).second;
        cout << diameter << '\n';
    }
    return 0;
}
