#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;                 // N < 25

int N;
vector<int> adj[MAXN];

int disc[MAXN], low[MAXN], timer_;
bool isArt[MAXN];
vector<pair<int,int>> edgeStack;     // stack of edges for Tarjan
vector<vector<int>> components;      // each component = list of its vertices (may contain duplicates)

// ------------------------------------------------------------
// Tarjan DFS for biconnected components
void dfs(int u, int parent) {
    disc[u] = low[u] = ++timer_;
    int childCnt = 0;
    for (int v : adj[u]) {
        if (!disc[v]) {
            edgeStack.emplace_back(u, v);
            ++childCnt;
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= disc[u]) {          // u is an articulation point for this component
                if (parent != -1 || childCnt > 1)
                    isArt[u] = true;

                // pop edges to form one component
                vector<int> comp;
                while (true) {
                    auto e = edgeStack.back(); edgeStack.pop_back();
                    comp.push_back(e.first);
                    comp.push_back(e.second);
                    if (e.first == u && e.second == v) break;
                }
                // remove duplicate vertices
                sort(comp.begin(), comp.end());
                comp.erase(unique(comp.begin(), comp.end()), comp.end());
                components.push_back(comp);
            }
        } else if (v != parent && disc[v] < disc[u]) {
            // back edge, push only once (disc[v] < disc[u] avoids double push)
            edgeStack.emplace_back(u, v);
            low[u] = min(low[u], disc[v]);
        }
    }

    // root articulation test (handled inside loop)
    if (parent == -1 && childCnt > 1)
        isArt[u] = true;
}

// ------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N) {
        // clear previous data
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            disc[i] = low[i] = 0;
            isArt[i] = false;
        }
        components.clear();
        edgeStack.clear();
        timer_ = 0;

        // read edges
        int a, b;
        while (cin >> a) {
            if (a == 0) break;
            cin >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // run Tarjan
        for (int i = 1; i <= N; ++i)
            if (!disc[i])
                dfs(i, -1);

        // after DFS there may be leftover edges (for isolated component)
        if (!edgeStack.empty()) {
            vector<int> comp;
            while (!edgeStack.empty()) {
                auto e = edgeStack.back(); edgeStack.pop_back();
                comp.push_back(e.first);
                comp.push_back(e.second);
            }
            sort(comp.begin(), comp.end());
            comp.erase(unique(comp.begin(), comp.end()), comp.end());
            components.push_back(comp);
        }

        // count answer
        int answer = 0;
        bool covered[MAXN] = {false};

        for (const auto& comp : components) {
            bool hasNonArt = false;
            for (int v : comp)
                if (!isArt[v]) { hasNonArt = true; break; }
            if (hasNonArt) {
                ++answer;
                for (int v : comp) covered[v] = true;
            }
        }

        for (int v = 1; v <= N; ++v)
            if (!covered[v])
                ++answer;          // singleton (isolated or uncovered articulation)

        cout << answer << '\n';
    }
    return 0;
}
