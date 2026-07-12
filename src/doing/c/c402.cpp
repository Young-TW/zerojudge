#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];
int color[MAXN];
int power[MAXN];
int n, m;

bool bfs(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                q.push(v);
            } else if (color[v] == color[u]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            cin >> power[i];
            adj[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        memset(color, -1, sizeof(color));
        bool possible = true;
        for (int i = 1; i <= n; i++) {
            if (color[i] == -1) {
                if (!bfs(i)) {
                    possible = false;
                    break;
                }
            }
        }

        if (!possible) {
            cout << "Bye Bye Cruel World!" << endl;
        } else {
            int sum0 = 0, sum1 = 0;
            for (int i = 1; i <= n; i++) {
                if (color[i] == 0) {
                    sum0 += power[i];
                } else {
                    sum1 += power[i];
                }
            }
            if (sum0 < sum1) {
                cout << sum0 << " " << sum1 << endl;
            } else {
                cout << sum1 << " " << sum0 << endl;
            }
        }
    }
    return 0;
}
