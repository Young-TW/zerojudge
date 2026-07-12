#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int dp[1 << 17][17];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<vector<int>> A(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> A[i][j];
            }
        }

        int max_mask = 1 << N;
        
        for (int mask = 0; mask < max_mask; ++mask) {
            for (int i = 0; i < N; ++i) {
                dp[mask][i] = INF;
            }
        }

        for (int i = 0; i < N; ++i) {
            dp[max_mask - 1][i] = 0;
        }

        for (int mask = max_mask - 2; mask >= 1; --mask) {
            for (int i = 0; i < N; ++i) {
                if (!(mask & (1 << i))) continue;
                int min_val = INF;
                for (int j = 0; j < N; ++j) {
                    if (mask & (1 << j)) continue;
                    int next_mask = mask | (1 << j);
                    if (dp[next_mask][j] != INF) {
                        min_val = min(min_val, dp[next_mask][j] + A[i][j]);
                    }
                }
                dp[mask][i] = min_val;
            }
        }

        int min_cost = INF;
        int start_node = -1;
        for (int i = 0; i < N; ++i) {
            if (dp[1 << i][i] < min_cost) {
                min_cost = dp[1 << i][i];
                start_node = i;
            }
        }

        vector<int> path;
        path.push_back(start_node);
        int current_mask = 1 << start_node;
        int current_node = start_node;

        while (current_mask != max_mask - 1) {
            for (int j = 0; j < N; ++j) {
                if (current_mask & (1 << j)) continue;
                int next_mask = current_mask | (1 << j);
                if (dp[next_mask][j] + A[current_node][j] == dp[current_mask][current_node]) {
                    path.push_back(j);
                    current_mask = next_mask;
                    current_node = j;
                    break;
                }
            }
        }

        cout << min_cost << "\n";
        for (int i = 0; i < N; ++i) {
            cout << path[i] + 1 << (i == N - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
