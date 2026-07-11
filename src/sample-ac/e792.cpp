#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    while (cin >> N >> M >> Q) {
        vector<vector<bool>> reachable(N, vector<bool>(N, false));
        
        for (int i = 0; i < N; ++i) {
            reachable[i][i] = true;
        }
        
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            if (u >= 0 && u < N && v >= 0 && v < N) {
                reachable[u][v] = true;
            }
        }
        
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                if (reachable[i][k]) {
                    for (int j = 0; j < N; ++j) {
                        if (reachable[k][j]) {
                            reachable[i][j] = true;
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < Q; ++i) {
            int a, b;
            cin >> a >> b;
            if (a >= 0 && a < N && b >= 0 && b < N && reachable[a][b]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    
    return 0;
}
