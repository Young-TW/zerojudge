#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        
        vector<int> lc(n, -1), rc(n, -1);
        vector<int> st;
        st.reserve(n);
        for (int i = 0; i < n; i++) {
            int last = -1;
            while (!st.empty() && a[st.back()] > a[i]) {
                last = st.back();
                st.pop_back();
            }
            if (!st.empty()) rc[st.back()] = i;
            if (last != -1) lc[i] = last;
            st.push_back(i);
        }
        
        int root = st.empty() ? 0 : st[0];
        
        // Compute subtree sums via iterative post-order
        vector<long long> sum(n, 0);
        vector<int> order;
        order.reserve(n);
        st.clear();
        st.push_back(root);
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            if (lc[u] != -1) st.push_back(lc[u]);
            if (rc[u] != -1) st.push_back(rc[u]);
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            sum[u] = a[u];
            if (lc[u] != -1) sum[u] += sum[lc[u]];
            if (rc[u] != -1) sum[u] += sum[rc[u]];
        }
        
        // Traverse from root
        int cur = root;
        while (lc[cur] != -1 || rc[cur] != -1) {
            long long ls = (lc[cur] != -1) ? sum[lc[cur]] : 0;
            long long rs = (rc[cur] != -1) ? sum[rc[cur]] : 0;
            if (ls > rs) cur = lc[cur];
            else cur = rc[cur];
        }
        printf("%d\n", a[cur]);
    }
    return 0;
}
