#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    while (cin >> N >> Q) {
        vector<vector<int> > children(N + 1);
        for (int i = 2; i <= N; i++) {
            int f;
            cin >> f;
            children[f].push_back(i);
        }
        
        vector<int> tin(N + 1), tout(N + 1), depth(N + 1);
        int timer = 0;
        
        stack<pair<int, int> > stk;
        stk.push(make_pair(1, 0));
        depth[1] = 0;
        while (!stk.empty()) {
            pair<int, int> top = stk.top();
            stk.pop();
            int node = top.first;
            int state = top.second;
            if (state == 0) {
                tin[node] = timer++;
                stk.push(make_pair(node, 1));
                for (int i = (int)children[node].size() - 1; i >= 0; i--) {
                    int c = children[node][i];
                    depth[c] = depth[node] + 1;
                    stk.push(make_pair(c, 0));
                }
            } else {
                tout[node] = timer - 1;
            }
        }
        
        int maxDepth = 0;
        for (int i = 1; i <= N; i++) {
            if (depth[i] > maxDepth) maxDepth = depth[i];
        }
        vector<vector<int> > byDepth(maxDepth + 1);
        for (int i = 1; i <= N; i++) {
            byDepth[depth[i]].push_back(i);
        }
        
        vector<int> X(Q), K(Q), threshold(Q);
        for (int i = 0; i < Q; i++) {
            cin >> X[i] >> K[i];
            threshold[i] = depth[X[i]] + K[i];
            if (threshold[i] > maxDepth) threshold[i] = maxDepth;
        }
        
        vector<int> idx(Q);
        for (int i = 0; i < Q; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return threshold[a] < threshold[b];
        });
        
        int size = 1;
        while (size < N) size *= 2;
        if (size < 1) size = 1;
        vector<int> seg(2 * size, 0);
        
        vector<int> ans(Q, 0);
        int curDepth = -1;
        for (int q = 0; q < Q; q++) {
            int qi = idx[q];
            int t = threshold[qi];
            while (curDepth < t) {
                curDepth++;
                if (curDepth <= maxDepth) {
                    for (size_t j = 0; j < byDepth[curDepth].size(); j++) {
                        int v = byDepth[curDepth][j];
                        int pos = tin[v] + size;
                        if (v > seg[pos]) seg[pos] = v;
                        for (pos /= 2; pos >= 1; pos /= 2) {
                            int newVal = seg[2 * pos];
                            if (seg[2 * pos + 1] > newVal) newVal = seg[2 * pos + 1];
                            seg[pos] = newVal;
                        }
                    }
                }
            }
            int l = tin[X[qi]] + size;
            int r = tout[X[qi]] + size;
            int res = 0;
            while (l <= r) {
                if (l & 1) {
                    if (seg[l] > res) res = seg[l];
                    l++;
                }
                if (!(r & 1)) {
                    if (seg[r] > res) res = seg[r];
                    r--;
                }
                l /= 2;
                r /= 2;
            }
            ans[qi] = res;
        }
        
        for (int i = 0; i < Q; i++) {
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
