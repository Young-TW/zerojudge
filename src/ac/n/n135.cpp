#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int lcs(const int* A, const int* B, int n) {
    int dp[505] = {0};
    int next_dp[505] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (A[i-1] == B[j-1]) {
                next_dp[j] = dp[j-1] + 1;
            } else {
                next_dp[j] = (dp[j] > next_dp[j-1]) ? dp[j] : next_dp[j-1];
            }
        }
        memcpy(dp, next_dp, sizeof(int) * (n + 1));
    }
    return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        vector<int> d(M);
        vector<int> routes(M * (N + 1));
        for (int i = 0; i < M; ++i) {
            cin >> d[i];
            for (int j = 0; j <= N; ++j) {
                cin >> routes[i * (N + 1) + j];
            }
        }
        
        int best_idx = 0;
        for (int i = 1; i < M; ++i) {
            if (d[i] < d[best_idx]) {
                best_idx = i;
            }
        }
        
        vector<pair<int, int>> items(M);
        for (int i = 0; i < M; ++i) {
            int l = lcs(routes.data() + best_idx * (N + 1), routes.data() + i * (N + 1), N + 1);
            items[i] = {l, d[i]};
        }
        
        sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
        
        vector<int> dp_lis(M, 1);
        int max_len = 0;
        for (int i = 0; i < M; ++i) {
            dp_lis[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (items[j].second > items[i].second) {
                    if (dp_lis[j] + 1 > dp_lis[i]) {
                        dp_lis[i] = dp_lis[j] + 1;
                    }
                }
            }
            if (dp_lis[i] > max_len) {
                max_len = dp_lis[i];
            }
        }
        cout << max_len << "\n";
    }
    return 0;
}
