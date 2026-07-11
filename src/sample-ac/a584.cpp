#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        map<string, vector<string>> adj;
        for (int i = 0; i < n; ++i) {
            string line;
            do {
                if (!getline(cin, line)) return 0;
            } while (line.empty());
            stringstream ss(line);
            string p;
            ss >> p;
            string c;
            while (ss >> c) {
                adj[p].push_back(c);
                adj[c].push_back(p);
            }
        }
        string line;
        do {
            if (!getline(cin, line)) return 0;
        } while (line.empty());
        stringstream ss(line);
        string A, B;
        ss >> A >> B;

        map<string, int> dist;
        queue<string> q;
        q.push(A);
        dist[A] = 0;
        while (!q.empty()) {
            string u = q.front();
            q.pop();
            if (u == B) break;
            for (const string& v : adj[u]) {
                if (dist.find(v) == dist.end()) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        cout << dist[B] << "\n";
    }
    return 0;
}
