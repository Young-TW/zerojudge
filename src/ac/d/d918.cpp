#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        
        vector<int> Es(m);
        for (int i = 0; i < m; ++i) {
            string s;
            cin >> s;
            if (s == "l") Es[i] = 1;
            else Es[i] = stoi(s);
        }
        
        vector<int> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int K = vals.size();
        int min_a = vals.front();
        int max_a = vals.back();
        
        vector<int> ans(m);
        for (int e_idx = 0; e_idx < m; ++e_idx) {
            int E = Es[e_idx];
            if (E >= max_a - min_a) {
                ans[e_idx] = n;
                continue;
            }
            vector<int> best(K, 0);
            vector<int> old_best(K);
            for (int i = 0; i < n; ++i) {
                int x = a[i];
                int xi = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
                old_best = best;
                if (best[xi] < 1) best[xi] = 1;
                int limit_idx = upper_bound(vals.begin(), vals.end(), x + E) - vals.begin();
                for (int v_idx = 0; v_idx < limit_idx; ++v_idx) {
                    int L = old_best[v_idx];
                    if (L == 0) continue;
                    int v = vals[v_idx];
                    int new_idx = (v >= x) ? v_idx : xi;
                    int new_len = L + 1;
                    if (new_len > best[new_idx]) best[new_idx] = new_len;
                }
            }
            ans[e_idx] = *max_element(best.begin(), best.end());
        }
        
        for (int i = 0; i < m; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
