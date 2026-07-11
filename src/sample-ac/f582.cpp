#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <array>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> par(n+1);
        vector<string> seq(n+1);
        int root = -1;
        vector<vector<int>> ch(n+1);
        for (int k = 0; k < n; k++) {
            int id, p;
            string s;
            cin >> id >> p >> s;
            par[id] = p;
            seq[id] = s;
            if (id == p) root = id;
        }
        for (int i = 1; i <= n; i++) {
            if (i != root) ch[par[i]].push_back(i);
        }
        
        auto cidx = [](char c) -> int {
            if (c == 'A') return 0;
            if (c == 'U') return 1;
            if (c == 'C') return 2;
            if (c == 'G') return 3;
            return -1;
        };
        
        const int INF = 1e9;
        long long total = 0;
        
        vector<int> order;
        order.reserve(n);
        {
            stack<int> stk;
            stk.push(root);
            while (!stk.empty()) {
                int u = stk.top(); stk.pop();
                order.push_back(u);
                for (int v : ch[u]) stk.push(v);
            }
            reverse(order.begin(), order.end());
        }
        
        vector<array<int,4>> dp(n+1);
        
        for (int pos = 0; pos < m; pos++) {
            for (int u : order) {
                for (int c = 0; c < 4; c++) dp[u][c] = 0;
                for (int v : ch[u]) {
                    for (int c = 0; c < 4; c++) {
                        int best = INF;
                        for (int c2 = 0; c2 < 4; c2++) {
                            int val = dp[v][c2] + (c != c2 ? 1 : 0);
                            if (val < best) best = val;
                        }
                        dp[u][c] += best;
                    }
                }
                int fixed = cidx(seq[u][pos]);
                if (fixed != -1) {
                    for (int c = 0; c < 4; c++) {
                        if (c != fixed) dp[u][c] = INF;
                    }
                }
            }
            int bestRoot = INF;
            for (int c = 0; c < 4; c++) bestRoot = min(bestRoot, dp[root][c]);
            total += bestRoot;
        }
        
        cout << total << "\n";
    }
    return 0;
}
