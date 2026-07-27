#include <bits/stdc++.h>
using namespace std;

int n, m;
int nxtId;
vector<vector<pair<int,char>>> adj;
vector<int> indeg;
vector<int> distv;

// Segment tree arrays, indexed by node ID
vector<int> segL, segR, segLeft, segRight;

int buildSeg(int l, int r) {
    if (l == r) return l;
    int cur = ++nxtId;
    int mid = (l + r) >> 1;
    int leftId = buildSeg(l, mid);
    int rightId = buildSeg(mid + 1, r);
    segLeft[cur] = leftId;
    segRight[cur] = rightId;
    segL[cur] = l;
    segR[cur] = r;
    adj[leftId].push_back({cur, 0});
    adj[rightId].push_back({cur, 0});
    indeg[cur] += 2;
    return cur;
}

void addRange(int nodeId, int ql, int qr, int v) {
    if (nodeId <= n) {
        // leaf node, nodeId is the station ID
        if (ql <= nodeId && nodeId <= qr) {
            adj[nodeId].push_back({v, 1});
            indeg[v]++;
        }
        return;
    }
    int l = segL[nodeId], r = segR[nodeId];
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        adj[nodeId].push_back({v, 1});
        indeg[v]++;
        return;
    }
    addRange(segLeft[nodeId], ql, qr, v);
    addRange(segRight[nodeId], ql, qr, v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        nxtId = n;
        int maxNodes = 4 * n + m + 10;
        adj.assign(maxNodes, {});
        indeg.assign(maxNodes, 0);
        distv.assign(maxNodes, 0);
        segL.assign(maxNodes, 0);
        segR.assign(maxNodes, 0);
        segLeft.assign(maxNodes, -1);
        segRight.assign(maxNodes, -1);
        
        int root = buildSeg(1, n);
        
        for (int ti = 0; ti < m; ++ti) {
            int s;
            cin >> s;
            vector<int> stop(s);
            for (int i = 0; i < s; ++i) cin >> stop[i];
            int vNode = ++nxtId;
            for (int i = 0; i + 1 < s; ++i) {
                int L = stop[i] + 1;
                int R = stop[i + 1] - 1;
                if (L <= R) {
                    addRange(root, L, R, vNode);
                }
            }
            for (int st : stop) {
                adj[vNode].push_back({st, 0});
                indeg[st]++;
            }
        }
        
        int totalVertices = nxtId;
        
        // Initialize dist for stations
        for (int i = 1; i <= n; ++i) distv[i] = 1;
        
        queue<int> q;
        for (int i = 1; i <= totalVertices; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& e : adj[u]) {
                int v = e.first;
                char w = e.second;
                int nd = distv[u] + w;
                if (distv[v] < nd) distv[v] = nd;
                if (--indeg[v] == 0) q.push(v);
            }
        }
        
        int answer = 0;
        for (int i = 1; i <= n; ++i) answer = max(answer, distv[i]);
        cout << answer << '\n';
    }
    return 0;
}
