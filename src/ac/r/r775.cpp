#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> adj(N, vector<int>(N, 0));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> adj[i][j];
            }
        }
        
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                if (adj[i][k]) {
                    for (int j = 0; j < N; ++j) {
                        if (adj[k][j]) {
                            adj[i][j] = 1;
                        }
                    }
                }
            }
        }
        
        vector<int> route(M);
        for (int i = 0; i < M; ++i) {
            cin >> route[i];
            route[i]--;
        }
        
        bool possible = true;
        for (int i = 0; i < M - 1; ++i) {
            if (route[i] == route[i+1]) continue;
            if (!adj[route[i]][route[i+1]]) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
