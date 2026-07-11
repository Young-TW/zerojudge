#include <iostream>

using namespace std;

int parent[100005];
int deg[100005];

int find(int x) {
    return parent[x] == x ? x : (parent[x] = find(parent[x]));
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            parent[i] = i;
            deg[i] = 0;
        }
        
        bool possible = true;
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            if (!possible) continue;
            
            deg[u]++;
            deg[v]++;
            
            if (deg[u] > 2 || deg[v] > 2) {
                possible = false;
                continue;
            }
            
            if (find(u) == find(v)) {
                possible = false;
            } else {
                unionSet(u, v);
            }
        }
        
        if (possible) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
