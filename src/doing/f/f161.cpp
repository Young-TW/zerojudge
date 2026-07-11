#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<int> weights(N);
        for (int i = 0; i < N; ++i) {
            cin >> weights[i];
        }
        vector<vector<int>> adj(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> tails;
        int max_len = 0;
        
        if (N > 0) {
            struct StackFrame {
                int u;
                int p;
                int child_idx;
                bool is_push;
                int old_val;
                int old_idx;
            };
            vector<StackFrame> st;
            st.push_back({0, -1, 0, false, -1, -1});
            
            int w = weights[0];
            auto it = upper_bound(tails.begin(), tails.end(), w);
            if (it == tails.end()) {
                tails.push_back(w);
                st.back().is_push = true;
            } else {
                st.back().old_idx = distance(tails.begin(), it);
                st.back().old_val = *it;
                *it = w;
            }
            max_len = max(max_len, (int)tails.size());
            
            while (!st.empty()) {
                StackFrame& top = st.back();
                if (top.child_idx < (int)adj[top.u].size()) {
                    int v = adj[top.u][top.child_idx];
                    top.child_idx++;
                    if (v != top.p) {
                        st.push_back({v, top.u, 0, false, -1, -1});
                        int w_child = weights[v];
                        auto it_child = upper_bound(tails.begin(), tails.end(), w_child);
                        if (it_child == tails.end()) {
                            tails.push_back(w_child);
                            st.back().is_push = true;
                        } else {
                            st.back().old_idx = distance(tails.begin(), it_child);
                            st.back().old_val = *it_child;
                            *it_child = w_child;
                        }
                        max_len = max(max_len, (int)tails.size());
                    }
                } else {
                    if (top.is_push) {
                        tails.pop_back();
                    } else if (top.old_idx != -1) {
                        tails[top.old_idx] = top.old_val;
                    }
                    st.pop_back();
                }
            }
        }
        cout << max_len << "\n";
    }
    return 0;
}
