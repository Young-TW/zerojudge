#include <iostream>
#include <vector>
#include <stack>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    while (std::cin >> n) {
        std::vector<std::vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        /* 1. root the tree at 1, obtain parent[] and a traversal order */
        std::vector<int> parent(n + 1, 0);
        std::vector<int> order;
        order.reserve(n);
        std::stack<int> st;
        st.push(1);
        parent[1] = -1;                 // mark root's parent specially

        while (!st.empty()) {
            int v = st.top(); st.pop();
            order.push_back(v);
            for (int to : adj[v]) {
                if (to == parent[v]) continue;
                parent[to] = v;
                st.push(to);
            }
        }

        /* 2. subtree sizes */
        std::vector<int> sub(n + 1, 1);
        for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
            int v = order[i];
            for (int to : adj[v]) {
                if (to == parent[v]) continue;   // child only
                sub[v] += sub[to];
            }
        }

        long long total = static_cast<long long>(n - 1);
        long long totalSq = total * total;

        long long bestVal = -1;
        int bestIdx = 1;

        for (int v = 1; v <= n; ++v) {
            long long sumSq = 0;
            for (int to : adj[v]) {
                long long comp;
                if (to == parent[v]) {          // component that contains the parent
                    comp = static_cast<long long>(n - sub[v]);
                } else {                         // child component
                    comp = static_cast<long long>(sub[to]);
                }
                sumSq += comp * comp;
            }
            long long paths = (totalSq - sumSq) / 2;   // Σ_{i<j} si·sj
            if (paths > bestVal || (paths == bestVal && v < bestIdx)) {
                bestVal = paths;
                bestIdx = v;
            }
        }

        std::cout << bestIdx << ' ' << bestVal << '\n';
    }
    return 0;
}
