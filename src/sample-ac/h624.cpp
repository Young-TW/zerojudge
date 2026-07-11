#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<vector<int>> adj(N + 1);
        for (int i = 1; i <= N; ++i) {
            int M;
            cin >> M;
            adj[i].resize(M);
            for (int j = 0; j < M; ++j) {
                cin >> adj[i][j];
            }
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        }
        
        vector<int> first_copy(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            for (int j : adj[i]) {
                if (first_copy[j] == 0) {
                    first_copy[j] = i;
                }
            }
        }
        
        long long ans = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j : adj[i]) {
                int k = first_copy[j];
                if (k != 0 && first_copy[k] == i) {
                    ans++;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
