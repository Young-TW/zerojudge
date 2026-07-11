#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, k;
vector<int> pairU, pairV, dist_;
vector<vector<int>> adj;

bool bfs() {
    queue<int> q;
    bool found = false;
    for (int u = 0; u < n; u++) {
        if (pairU[u] == -1) {
            dist_[u] = 0;
            q.push(u);
        } else {
            dist_[u] = -1;
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 != -1 && dist_[u2] == -1) {
                dist_[u2] = dist_[u] + 1;
                q.push(u2);
            } else if (u2 == -1) {
                found = true;
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int v : adj[u]) {
        int u2 = pairV[v];
        if (u2 == -1 || (dist_[u2] == dist_[u] + 1 && dfs(u2))) {
            pairU[u] = v;
            pairV[v] = u;
            return true;
        }
    }
    dist_[u] = -1;
    return false;
}

bool check(long long T, const vector<vector<long long>>& D) {
    adj.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (D[i][j] <= T) {
                adj[i].push_back(j);
            }
        }
    }
    pairU.assign(n, -1);
    pairV.assign(n, -1);
    dist_.assign(n, -1);
    int matching = 0;
    while (bfs()) {
        for (int u = 0; u < n; u++) {
            if (pairU[u] == -1) {
                if (dfs(u)) matching++;
            }
        }
    }
    return matching == n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> k) {
        vector<vector<long long>> A(n, vector<long long>(k));
        vector<vector<long long>> B(n, vector<long long>(k));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < k; j++)
                cin >> A[i][j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < k; j++)
                cin >> B[i][j];
        
        vector<vector<long long>> D(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long s = 0;
                for (int t = 0; t < k; t++) {
                    s += A[i][t] * B[j][t];
                }
                D[i][j] = s;
            }
        }
        
        vector<long long> vals;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                vals.push_back(D[i][j]);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        
        int lo = 0, hi = (int)vals.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (check(vals[mid], D)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        cout << vals[lo] << "\n";
    }
    return 0;
}
