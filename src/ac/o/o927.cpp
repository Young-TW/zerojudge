#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;
vector<int> V_cnt;
vector<int> E_cnt;

int find(int i) {
    int root = i;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (parent[i] != root) {
        int next = parent[i];
        parent[i] = root;
        i = next;
    }
    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        parent.resize(n);
        V_cnt.assign(n, 1);
        E_cnt.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            int root_u = find(u);
            int root_v = find(v);
            if (root_u != root_v) {
                parent[root_u] = root_v;
                V_cnt[root_v] += V_cnt[root_u];
                E_cnt[root_v] += E_cnt[root_u];
            }
            E_cnt[root_v]++;
        }
        int cyclic = 0, acyclic = 0;
        for (int i = 0; i < n; ++i) {
            if (find(i) == i) {
                if (E_cnt[i] >= V_cnt[i]) {
                    cyclic++;
                } else {
                    acyclic++;
                }
            }
        }
        cout << cyclic << " " << acyclic << "\n";
    }
    return 0;
}
