#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<int> vals(N);
        for (int i = 0; i < N; ++i) {
            cin >> vals[i];
        }

        vector<int> sorted_vals = vals;
        sort(sorted_vals.begin(), sorted_vals.end());

        vector<int> depth(N, 0);
        vector<int> left_child(N, -1);
        vector<int> right_child(N, -1);
        
        set<int> s;
        int root = -1;

        for (int i = 0; i < N; ++i) {
            int val = vals[i];
            int idx = lower_bound(sorted_vals.begin(), sorted_vals.end(), val) - sorted_vals.begin();
            
            if (i == 0) {
                root = idx;
                depth[idx] = 0;
                s.insert(idx);
                continue;
            }

            auto it = s.insert(idx).first;
            int pred = -1, succ = -1;
            
            if (it != s.begin()) {
                pred = *prev(it);
            }
            if (next(it) != s.end()) {
                succ = *next(it);
            }

            if (pred != -1 && succ != -1) {
                if (depth[pred] > depth[succ]) {
                    right_child[pred] = idx;
                    depth[idx] = depth[pred] + 1;
                } else {
                    left_child[succ] = idx;
                    depth[idx] = depth[succ] + 1;
                }
            } else if (pred != -1) {
                right_child[pred] = idx;
                depth[idx] = depth[pred] + 1;
            } else {
                left_child[succ] = idx;
                depth[idx] = depth[succ] + 1;
            }
        }

        vector<int> result;
        result.reserve(N);
        vector<int> stk;
        stk.push_back(root);
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            result.push_back(sorted_vals[u]);
            if (right_child[u] != -1) {
                stk.push_back(right_child[u]);
            }
            if (left_child[u] != -1) {
                stk.push_back(left_child[u]);
            }
        }

        for (int i = 0; i < N; ++i) {
            cout << result[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
