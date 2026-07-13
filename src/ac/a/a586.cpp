#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

struct State {
    int cost, u, r;
    bool operator>(const State& o) const {
        return cost > o.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        map<string, int> id;
        vector<pair<string, string>> raw_edges;
        for (int i = 0; i < N; ++i) {
            string u, v;
            cin >> u >> v;
            raw_edges.push_back({u, v});
            if (id.find(u) == id.end()) id[u] = id.size();
            if (id.find(v) == id.end()) id[v] = id.size();
        }
        string start_str, end_str;
        if (!(cin >> start_str >> end_str)) break;
        if (id.find(start_str) == id.end()) id[start_str] = id.size();
        if (id.find(end_str) == id.end()) id[end_str] = id.size();
        
        int V = id.size();
        vector<char> line_char(V);
        for (auto& p : id) {
            line_char[p.second] = p.first[0];
        }
        
        vector<vector<int>> adj(V);
        for (auto& e : raw_edges) {
            int u = id[e.first];
            int v = id[e.second];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        int start = id[start_str];
        int end = id[end_str];
        
        const int INF = 1e9;
        vector<array<int, 3>> dist(V, {INF, INF, INF});
        priority_queue<State, vector<State>, greater<State>> pq;
        
        dist[start][0] = 0;
        pq.push({0, start, 0});
        
        while (!pq.empty()) {
            State curr = pq.top();
            pq.pop();
            
            if (curr.cost > dist[curr.u][curr.r]) continue;
            
            for (int v : adj[curr.u]) {
                int nr = (curr.r + 1) % 3;
                int cost = curr.cost;
                if (curr.r == 2) cost += 15;
                if (line_char[curr.u] != line_char[v]) cost += 15;
                
                if (cost < dist[v][nr]) {
                    dist[v][nr] = cost;
                    pq.push({cost, v, nr});
                }
            }
        }
        
        int min_dist = min({dist[end][0], dist[end][1], dist[end][2]});
        if (min_dist == INF) {
            cout << 0 << "\n";
        } else {
            cout << (30 + min_dist) / 3 << "\n";
        }
    }
    return 0;
}
