#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <cstdio>

using namespace std;

char buf[1 << 20], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
inline bool readInt(int &x) {
    char c;
    while (c = gc(), c != EOF && (c < '0' || c > '9'));
    if (c == EOF) return false;
    x = 0;
    do {
        x = x * 10 + (c - '0');
    } while (c = gc(), c >= '0' && c <= '9');
    return true;
}

long long solve_country(int n, int t, int m) {
    vector<int> ports(t);
    for (int i = 0; i < t; ++i) {
        readInt(ports[i]);
    }
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        readInt(u);
        readInt(v);
        readInt(c);
        adj[u].push_back(make_pair(v, c));
        adj[v].push_back(make_pair(u, c));
    }
    
    const long long INF = 1e18;
    long long min_max_dist = INF;
    
    for (int i = 0; i < t; ++i) {
        int p = ports[i];
        vector<long long> dist(n + 1, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[p] = 0;
        pq.push(make_pair(0, p));
        
        long long max_dist = 0;
        int visited_count = 0;
        
        while (!pq.empty()) {
            pair<long long, int> top = pq.top();
            pq.pop();
            long long d = top.first;
            int u = top.second;
            
            if (d > dist[u]) continue;
            
            visited_count++;
            if (d > max_dist) max_dist = d;
            
            for (size_t j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j].first;
                int c = adj[u][j].second;
                if (dist[u] + c < dist[v]) {
                    dist[v] = dist[u] + c;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        
        if (visited_count != n) {
            continue;
        }
        
        if (max_dist < min_max_dist) {
            min_max_dist = max_dist;
        }
    }
    return min_max_dist;
}

int main() {
    int n1, t1, m1;
    while (readInt(n1) && readInt(t1) && readInt(m1)) {
        long long ans1 = solve_country(n1, t1, m1);
        int n2, t2, m2;
        readInt(n2);
        readInt(t2);
        readInt(m2);
        long long ans2 = solve_country(n2, t2, m2);
        cout << ans1 + 1000 + ans2 << "\n";
    }
    return 0;
}
