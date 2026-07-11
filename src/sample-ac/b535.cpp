#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <utility>

using namespace std;

int parent[1005];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) parent[px] = py;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int k;
            cin >> k;
            cin.ignore();
            
            bool ok = true;
            set<int> internalNodes;
            set<pair<int,int> > usedEdges;
            
            for (int t = 0; t < k; t++) {
                string line;
                getline(cin, line);
                stringstream ss(line);
                
                vector<pair<int,int> > edges;
                set<int> nodes;
                string token;
                
                while (ss >> token) {
                    size_t dash = token.find('-');
                    int u = atoi(token.substr(0, dash).c_str());
                    int v = atoi(token.substr(dash+1).c_str());
                    if (u > v) swap(u, v);
                    edges.push_back(make_pair(u, v));
                    nodes.insert(u);
                    nodes.insert(v);
                }
                
                int n = (int)nodes.size();
                int m = (int)edges.size();
                
                if (m != n - 1) {
                    ok = false;
                    continue;
                }
                
                for (set<int>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
                    parent[*it] = *it;
                }
                
                for (size_t i = 0; i < edges.size(); i++) {
                    unite(edges[i].first, edges[i].second);
                }
                
                int root = -1;
                bool connected = true;
                for (set<int>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
                    if (root == -1) root = find(*it);
                    else if (find(*it) != root) { connected = false; break; }
                }
                if (!connected) {
                    ok = false;
                    continue;
                }
                
                for (size_t i = 0; i < edges.size(); i++) {
                    if (usedEdges.count(edges[i])) {
                        ok = false;
                    }
                    usedEdges.insert(edges[i]);
                }
                
                map<int,int> degree;
                for (size_t i = 0; i < edges.size(); i++) {
                    degree[edges[i].first]++;
                    degree[edges[i].second]++;
                }
                
                for (map<int,int>::iterator it = degree.begin(); it != degree.end(); ++it) {
                    if (it->second >= 2) {
                        if (internalNodes.count(it->first)) {
                            ok = false;
                        }
                        internalNodes.insert(it->first);
                    }
                }
            }
            
            cout << (ok ? "T" : "F") << "\n";
        }
    }
    
    return 0;
}
