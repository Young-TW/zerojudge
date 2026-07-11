#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 100005;

struct Edge {
    int to;
    int w;
    int next;
} edges[MAXN * 2];

int head[MAXN];
int edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].w = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int dp[MAXN], best[MAXN];
int max_d, mid_node, v1, v2;
int order[MAXN], parent[MAXN], q[MAXN];
int order_cnt = 0;

void bfs_order(int root) {
    int head_q = 0, tail_q = 0;
    q[tail_q++] = root;
    parent[root] = 0;
    order_cnt = 0;
    while (head_q < tail_q) {
        int u = q[head_q++];
        order[order_cnt++] = u;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (v == parent[u]) continue;
            parent[v] = u;
            q[tail_q++] = v;
        }
    }
}

void solve_dp() {
    for (int i = order_cnt - 1; i >= 0; i--) {
        int u = order[i];
        dp[u] = 0;
        best[u] = 0;
        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            int w = edges[j].w;
            if (v == parent[u]) continue;
            if (dp[v] + w > dp[u]) {
                dp[u] = dp[v] + w;
                best[u] = v;
            }
        }
        int sec = 0;
        int sec_v = 0;
        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            int w = edges[j].w;
            if (v == parent[u]) continue;
            if (v == best[u]) continue;
            if (dp[v] + w > sec) {
                sec = dp[v] + w;
                sec_v = v;
            }
        }
        if (dp[u] + sec > max_d) {
            max_d = dp[u] + sec;
            mid_node = u;
            v1 = best[u];
            v2 = sec_v;
        }
    }
}

void mark_path(int start, int p) {
    int curr = start;
    while (best[curr] != 0) {
        int next_v = best[curr];
        for (int i = head[curr]; i != -1; i = edges[i].next) {
            if (edges[i].to == next_v) {
                edges[i].w = -1;
                edges[i ^ 1].w = -1;
                break;
            }
        }
        curr = next_v;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, K;
    while (cin >> n >> K) {
        for (int i = 1; i <= n; i++) head[i] = -1;
        edge_cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v, 1);
            add_edge(v, u, 1);
        }
        
        bfs_order(1);
        max_d = 0;
        solve_dp();
        int D1 = max_d;
        
        if (K == 1) {
            cout << 2 * (n - 1) - D1 + 1 << "\n";
            continue;
        }
        
        if (v1 != 0) {
            for (int i = head[mid_node]; i != -1; i = edges[i].next) {
                if (edges[i].to == v1) {
                    edges[i].w = -1;
                    edges[i ^ 1].w = -1;
                    break;
                }
            }
            mark_path(v1, mid_node);
        }
        if (v2 != 0) {
            for (int i = head[mid_node]; i != -1; i = edges[i].next) {
                if (edges[i].to == v2) {
                    edges[i].w = -1;
                    edges[i ^ 1].w = -1;
                    break;
                }
            }
            mark_path(v2, mid_node);
        }
        
        max_d = 0;
        solve_dp();
        int D2 = max_d;
        
        cout << 2 * (n - 1) - D1 - D2 + 2 << "\n";
    }
    return 0;
}
