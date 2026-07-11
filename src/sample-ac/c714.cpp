#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<int> l(N + 1), r(N + 1);
            for (int i = 1; i <= N; ++i) {
                cin >> l[i] >> r[i];
            }
            vector<int> v(N + 1), w(N + 1);
            for (int i = 1; i <= N; ++i) cin >> v[i];
            for (int i = 1; i <= N; ++i) cin >> w[i];

            vector<int> inorder;
            inorder.reserve(N);
            vector<int> stack;
            stack.reserve(N);
            int curr = 1;
            while (curr != 0 || !stack.empty()) {
                while (curr != 0) {
                    stack.push_back(curr);
                    curr = l[curr];
                }
                curr = stack.back();
                stack.pop_back();
                inorder.push_back(curr);
                curr = r[curr];
            }

            vector<long long> B(N);
            vector<long long> W(N);
            long long total_weight = 0;
            for (int i = 0; i < N; ++i) {
                int node = inorder[i];
                B[i] = v[node] - (i + 1);
                W[i] = w[node];
                total_weight += W[i];
            }

            int M = 1;
            while (M <= 2 * N + 2) M <<= 1;
            vector<long long> tree(M * 2, 0);

            for (int i = 0; i < N; ++i) {
                int idx = B[i] + N + 1;
                long long max_val = 0;
                int l_idx = M;
                int r_idx = M + idx - 1;
                while (l_idx <= r_idx) {
                    if (l_idx % 2 == 1) max_val = max(max_val, tree[l_idx++]);
                    if (r_idx % 2 == 0) max_val = max(max_val, tree[r_idx--]);
                    l_idx /= 2;
                    r_idx /= 2;
                }

                long long new_val = max_val + W[i];
                int p = M + idx - 1;
                if (new_val > tree[p]) {
                    tree[p] = new_val;
                    p /= 2;
                    while (p >= 1) {
                        tree[p] = max(tree[2 * p], tree[2 * p + 1]);
                        p /= 2;
                    }
                }
            }

            cout << total_weight - tree[1] << "\n";
        }
    }

    return 0;
}
