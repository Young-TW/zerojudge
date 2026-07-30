// d459. 一棵小樹 — 以節點 1 為根,求每點子樹(含自身)節點數。
// 100% 自寫。重點:
//  1) n 可達 20000,鏈狀樹遞迴 DFS 會爆 stack → 改用 BFS 定序後反向累加子樹大小。
//  2) 只保留可解析為整數的 token(樣本含 "//此行不會出現在測資中" 註解行,真測資無)。
//  3) 輸出格式 printf("%5d-%5d\n", 節點, 子樹大小)。
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    // 讀入全部,過濾出整數 token
    std::ios::sync_with_stdio(false);
    string all, tok;
    {
        std::ostringstream ss; ss << cin.rdbuf(); all = ss.str();
    }
    vector<long long> vals;
    std::istringstream is(all);
    while (is >> tok) {
        bool ok = !tok.empty();
        size_t st = (tok[0] == '-' || tok[0] == '+') ? 1 : 0;
        if (st == tok.size()) ok = false;
        for (size_t i = st; i < tok.size() && ok; ++i)
            if (tok[i] < '0' || tok[i] > '9') ok = false;
        if (ok) vals.push_back(stoll(tok));
    }
    if (vals.empty()) return 0;
    size_t idx = 0;
    int n = (int)vals[idx++];
    vector<vector<int>> adj(n + 1);
    for (int e = 0; e < n - 1; ++e) {
        if (idx + 1 >= vals.size()) break;
        int u = (int)vals[idx++], v = (int)vals[idx++];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // BFS 由節點 1 定序,記父節點
    vector<int> order; order.reserve(n);
    vector<int> par(n + 1, 0);
    vector<char> vis(n + 1, 0);
    vector<int> stk; stk.push_back(1); vis[1] = 1; par[1] = 0;
    while (!stk.empty()) {
        int u = stk.back(); stk.pop_back();
        order.push_back(u);
        for (int w : adj[u]) if (!vis[w]) { vis[w] = 1; par[w] = u; stk.push_back(w); }
    }
    // 反向累加子樹大小
    vector<int> sz(n + 1, 1);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        if (par[u]) sz[par[u]] += sz[u];
    }
    for (int i = 1; i <= n; ++i) printf("%5d-%5d\n", i, sz[i]);
    return 0;
}
