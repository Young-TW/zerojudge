#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    long long t;
    while (cin >> n >> t) {
        vector<long long> A(n + 1);
        set<int> active_levels;
        set<pair<long long, int>> pq;
        
        for (int i = 1; i <= n; ++i) {
            cin >> A[i];
            if (A[i] > 0) {
                active_levels.insert(i);
                pq.insert({A[i], i});
            }
        }
        
        long long ans = 0;
        while (!pq.empty()) {
            auto it = pq.begin();
            long long w = it->first;
            int u = it->second;
            
            if (w > t) {
                break;
            }
            
            pq.erase(it);
            active_levels.erase(u);
            ans += w;
            
            auto next_it = active_levels.upper_bound(u);
            if (next_it != active_levels.end()) {
                int v = *next_it;
                pq.erase({A[v], v});
                A[v] += w;
                pq.insert({A[v], v});
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
