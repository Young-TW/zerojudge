#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const double EPS = 1e-8;

int N, E;
int C_init, M_init;
vector<int> adj[MAXN];
int dist[MAXN][MAXN];
int nxt[MAXN][MAXN];
double dp[MAXN][MAXN];
bool visited[MAXN][MAXN];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    dist[start][start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[start][v] == -1) {
                dist[start][v] = dist[start][u] + 1;
                q.push(v);
            }
        }
    }
}

double solve(int c, int m) {
    if (c == m) return 0.0;
    if (dist[c][m] <= 2) return 1.0;
    if (visited[c][m]) return dp[c][m];
    
    visited[c][m] = true;
    
    int c1 = nxt[c][m];
    int c2 = nxt[c1][m];
    
    double sum = 0.0;
    int p = adj[m].size();
    sum += solve(c2, m);
    for (int v : adj[m]) {
        sum += solve(c2, v);
    }
    
    dp[c][m] = sum / (p + 1) + 1.0;
    return dp[c][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> E) {
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            for (int j = 1; j <= N; ++j) {
                dist[i][j] = -1;
                nxt[i][j] = 0;
                visited[i][j] = false;
            }
        }

        cin >> C_init >> M_init;

        for (int i = 0; i < E; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= N; ++i) {
            bfs(i);
        }

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (i == j) {
                    nxt[i][j] = i;
                } else {
                    int min_d = dist[i][j];
                    int next_node = j;
                    for (int v : adj[i]) {
                        if (dist[v][j] < min_d) {
                            min_d = dist[v][j];
                            next_node = v;
                        } else if (dist[v][j] == min_d && v < next_node) {
                            next_node = v;
                        }
                    }
                    nxt[i][j] = next_node;
                }
            }
        }

        double ans = solve(C_init, M_init);

        cout << fixed << setprecision(3) << ans << "\n";
    }

    return 0;
}
