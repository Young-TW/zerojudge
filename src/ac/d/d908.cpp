#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> g[26];
int dp[26];
bool done[26];

int dfs(int v) {
    if (done[v]) return dp[v];
    done[v] = true;
    int best = 0;
    for (auto &e : g[v]) {
        int to = e.first;
        int w  = e.second;
        best = max(best, w + dfs(to));
    }
    dp[v] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char start;
    int n;
    while (cin >> start >> n) {
        for (int i = 0; i < 26; ++i) {
            g[i].clear();
            done[i] = false;
            dp[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            char a, b;
            int w;
            cin >> a >> b >> w;
            g[a - 'A'].push_back({b - 'A', w});
        }
        cout << dfs(start - 'A') << '\n';
    }
    return 0;
}
