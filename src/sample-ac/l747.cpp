#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    map<string, vector<string>> adj;

    for (int i = 0; i < T; ++i) {
        string u, v;
        if (!(cin >> u >> v)) return 0;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    string l, o;
    if (!(cin >> l >> o)) return 0;

    if (adj.find(l) == adj.end() || adj.find(o) == adj.end()) {
        cout << "False\n";
        return 0;
    }

    map<string, int> dist;
    queue<string> q;
    
    q.push(l);
    dist[l] = 0;

    while (!q.empty()) {
        string curr = q.front();
        q.pop();

        if (curr == o) {
            break;
        }

        for (const string& next : adj[curr]) {
            if (dist.find(next) == dist.end()) {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }

    if (dist.find(o) != dist.end()) {
        cout << "True " << dist[o] << "\n";
    } else {
        cout << "False\n";
    }

    return 0;
}
