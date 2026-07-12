#include <iostream>
#include <cstring>

using namespace std;

int n, k;
bool adj[105][105];
int max_count;
int best_set[105];
int current_set[105];

void dfs(int idx, int count, int* candidates, int num_candidates) {
    if (count + num_candidates - idx <= max_count) return;
    if (idx == num_candidates) {
        if (count > max_count) {
            max_count = count;
            for (int i = 0; i < count; ++i) {
                best_set[i] = current_set[i];
            }
        }
        return;
    }
    
    int u = candidates[idx];
    
    // 嘗試選 u
    int new_candidates[105];
    int new_num = 0;
    bool must_select = true;
    for (int i = idx + 1; i < num_candidates; ++i) {
        int v = candidates[i];
        if (!adj[u][v]) {
            new_candidates[new_num++] = v;
        } else {
            must_select = false;
        }
    }
    current_set[count] = u;
    dfs(0, count + 1, new_candidates, new_num);
    
    // 嘗試不選 u
    if (!must_select) {
        dfs(idx + 1, count, candidates, num_candidates);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            cin >> n >> k;
            memset(adj, 0, sizeof(adj));
            for (int i = 0; i < k; ++i) {
                int u, v;
                cin >> u >> v;
                adj[u][v] = adj[v][u] = true;
            }
            
            max_count = 0;
            int candidates[105];
            for (int i = 0; i < n; ++i) {
                candidates[i] = i + 1;
            }
            dfs(0, 0, candidates, n);
            
            cout << max_count << "\n";
            for (int i = 0; i < max_count; ++i) {
                cout << best_set[i];
                if (i < max_count - 1) cout << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
