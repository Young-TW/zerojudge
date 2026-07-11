#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
vector<int> adj[30];
int dfn[30], low[30], timer;
int stack_arr[30], top_idx;
bool in_stack[30];
int scc_count;
int scc_id[30];
int scc_size[30];

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stack_arr[++top_idx] = u;
    in_stack[u] = true;

    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (dfn[v] == 0) {
            tarjan(v);
            if (low[v] < low[u]) {
                low[u] = low[v];
            }
        } else if (in_stack[v]) {
            if (dfn[v] < low[u]) {
                low[u] = dfn[v];
            }
        }
    }

    if (low[u] == dfn[u]) {
        scc_count++;
        int current_scc_size = 0;
        int v;
        do {
            v = stack_arr[top_idx--];
            in_stack[v] = false;
            scc_id[v] = scc_count;
            current_scc_size++;
        } while (u != v);
        scc_size[scc_count] = current_scc_size;
    }
}

int main() {
    while (cin >> N) {
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            dfn[i] = 0;
            low[i] = 0;
            in_stack[i] = false;
            scc_id[i] = 0;
        }
        timer = 0;
        scc_count = 0;
        top_idx = 0;
        memset(scc_size, 0, sizeof(scc_size));

        int u, v;
        while (cin >> u && u != 0) {
            cin >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= N; ++i) {
            if (dfn[i] == 0) {
                tarjan(i);
            }
        }

        int result = 0;
        for (int i = 1; i <= scc_count; ++i) {
            if (scc_size[i] == 1) {
                result++;
            } else {
                result += 2;
            }
        }

        cout << result << endl;
    }
    return 0;
}
