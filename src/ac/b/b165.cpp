#include <bits/stdc++.h>
using namespace std;

int n, s;
vector<pair<int,int>> adj[305]; // (to, w)
long long dist_[305][305];

void bfsDist(int src) {
    // tree: DFS distances
    for (int i = 1; i <= n; i++) dist_[src][i] = -1;
    dist_[src][src] = 0;
    // iterative
    stack<int> st; st.push(src);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (auto &e : adj[u]) {
            if (dist_[src][e.first] < 0) {
                dist_[src][e.first] = dist_[src][u] + e.second;
                st.push(e.first);
            }
        }
    }
}

int parent_[305];
void buildParent(int src) {
    for (int i = 1; i <= n; i++) parent_[i] = 0;
    parent_[src] = -1;
    stack<int> st; st.push(src);
    vector<char> vis(n+1, 0); vis[src] = 1;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (auto &e : adj[u]) {
            if (!vis[e.first]) { vis[e.first]=1; parent_[e.first]=u; st.push(e.first); }
        }
    }
}

int main(){
    bool first = true;
    while (scanf("%d %d", &n, &s) == 2) {
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i < n-1; i++) {
            int a,b,w; scanf("%d %d %d", &a,&b,&w);
            adj[a].push_back({b,w});
            adj[b].push_back({a,w});
        }
        for (int i = 1; i <= n; i++) bfsDist(i);
        // find diameter endpoints
        int u=1, v=1; long long D=0;
        for (int i=1;i<=n;i++) for (int j=1;j<=n;j++)
            if (dist_[i][j] > D) { D=dist_[i][j]; u=i; v=j; }
        // path from u to v
        buildParent(u);
        vector<int> path;
        for (int x=v; x!=-1; x=parent_[x]) path.push_back(x);
        reverse(path.begin(), path.end()); // path[0]=u ... path[m]=v
        int m = (int)path.size()-1;
        // pre[i] = dist from u to path[i]
        vector<long long> pre(m+1);
        for (int i=0;i<=m;i++) pre[i]=dist_[u][path[i]];
        // f[t] = max off-diameter branch depth attached at path node t
        vector<long long> f(m+1, 0);
        for (int w=1; w<=n; w++) {
            long long best=LLONG_MAX; int bt=0;
            for (int t=0;t<=m;t++) {
                if (dist_[w][path[t]] < best) { best=dist_[w][path[t]]; bt=t; }
            }
            if (best > f[bt]) f[bt]=best;
        }
        long long ans = LLONG_MAX;
        for (int j=0;j<=m;j++) {
            long long branchmax = 0;
            for (int i=j; i>=0; i--) {
                if (pre[j]-pre[i] > s) break;
                if (f[i] > branchmax) branchmax = f[i];
                long long ecc = max(branchmax, max(pre[i], D - pre[j]));
                if (ecc < ans) ans = ecc;
            }
        }
        if (!first) printf("\n");
        first = false;
        printf("%lld\n", ans);
    }
    return 0;
}
