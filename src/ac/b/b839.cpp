#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int parent[55];

int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int getLCS(const string& s, const string& t) {
    int m = (int)s.length();
    int n = (int)t.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i-1] == t[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<string> names(N);
            for (int i = 0; i < N; ++i) {
                cin >> names[i];
                parent[i] = i;
            }
            
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    int lcs = getLCS(names[i], names[j]);
                    int min_len = (int)min(names[i].length(), names[j].length());
                    if (lcs * 2 >= min_len) {
                        unite(i, j);
                    }
                }
            }
            
            int group_size[55] = {0};
            int max_size = 0;
            for (int i = 0; i < N; ++i) {
                int root = find(i);
                group_size[root]++;
                if (group_size[root] > max_size) {
                    max_size = group_size[root];
                }
            }
            
            cout << max_size << "\n";
        }
    }
    return 0;
}
