#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        const int N = 2 * n;                 // we use indices up to 2n-1
        vector<long long> weight(N, 0);
        vector<int> left(N, 0), right(N, 0), parent(N, 0);

        // leaf weights
        for (int i = n; i <= 2 * n - 1; ++i) {
            long long w; cin >> w;
            weight[i] = w;
        }

        // cargos
        vector<long long> cargo(m);
        for (int i = 0; i < m; ++i) cin >> cargo[i];

        // tree structure
        for (int i = 0; i < n - 1; ++i) {
            int a, b, c; cin >> a >> b >> c;
            left[a] = b;
            right[a] = c;
            parent[b] = a;
            parent[c] = a;
        }

        /* post‑order traversal (iterative) to compute internal weights */
        vector<int> post;
        post.reserve(2 * n);
        vector<pair<int, bool>> st;
        st.emplace_back(1, false);               // root = 1
        while (!st.empty()) {
            auto cur = st.back(); st.pop_back();
            int v = cur.first;
            bool visited = cur.second;
            if (visited) {
                post.push_back(v);
            } else {
                st.emplace_back(v, true);
                if (right[v]) st.emplace_back(right[v], false);
                if (left[v])  st.emplace_back(left[v],  false);
            }
        }
        for (int v : post) {
            if (v >= n) continue;                // leaf, already has weight
            weight[v] = weight[left[v]] + weight[right[v]];
        }

        /* process cargos */
        vector<int> answer;
        answer.reserve(m);
        for (int i = 0; i < m; ++i) {
            long long w = cargo[i];
            int cur = 1;
            while (cur <= n - 1) {               // internal node
                int L = left[cur];
                int R = right[cur];
                if (weight[L] <= weight[R])
                    cur = L;
                else
                    cur = R;
            }
            int leaf = cur;
            answer.push_back(leaf);

            // update weights on the path leaf -> root
            int node = leaf;
            while (node != 0) {
                weight[node] += w;
                node = parent[node];
            }
        }

        for (size_t i = 0; i < answer.size(); ++i) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
    return 0;
}
