#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>

using namespace std;

int N, M;
vector<int> adj[35];
int match[40];
bool vis[40];

bool dfs(int u) {
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungarian() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < M; ++i) {
        memset(vis, false, sizeof(vis));
        if (dfs(i)) {
            res++;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string, int> size_to_id;
    size_to_id["XXL"] = 0;
    size_to_id["XL"] = 1;
    size_to_id["L"] = 2;
    size_to_id["M"] = 3;
    size_to_id["S"] = 4;
    size_to_id["XS"] = 5;

    while (cin >> N >> M) {
        for (int i = 0; i < M; ++i) {
            adj[i].clear();
        }
        int per_size = N / 6;
        for (int i = 0; i < M; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            int id1 = size_to_id[s1];
            int id2 = size_to_id[s2];
            for (int j = 0; j < per_size; ++j) {
                adj[i].push_back(id1 * per_size + j);
                adj[i].push_back(id2 * per_size + j);
            }
        }
        if (hungarian() == M) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
