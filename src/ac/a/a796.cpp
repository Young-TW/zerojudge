#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        int R;
        cin >> R;

        vector<vector<bool>> adj(N + 1, vector<bool>(N + 1, false));
        vector<int> degree(N + 1, 0);

        for (int i = 0; i < R; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u][v] = true;
            adj[v][u] = true;
            degree[u]++;
            degree[v]++;
        }

        int P;
        cin >> P;

        for (int i = 0; i < P; ++i) {
            int K;
            cin >> K;
            if (K == 1) {
                int A;
                cin >> A;
                cout << degree[A] << "\n";
            } else if (K == 2) {
                int A, B;
                cin >> A >> B;
                if (adj[A][B]) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            }
        }
    }

    return 0;
}
