#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        vector<long long> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        if (n == 1) {
            cout << 0 << "\n";
            continue;
        }
        int m = n - 1;
        vector<long long> d(m + 2);
        vector<int> L(m + 2), R(m + 2);
        vector<bool> del(m + 2, false);
        
        d[0] = 1e18;
        d[m + 1] = 1e18;
        L[0] = 0;
        R[0] = 1;
        L[m + 1] = m;
        R[m + 1] = m + 1;
        
        for (int i = 1; i <= m; ++i) {
            d[i] = s[i] - s[i - 1];
            L[i] = i - 1;
            R[i] = i + 1;
        }
        
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        for (int i = 1; i <= m; ++i) {
            pq.push({d[i], i});
        }
        
        long long ans = 0;
        for (int i = 0; i < k; ++i) {
            while (del[pq.top().second]) {
                pq.pop();
            }
            auto top = pq.top();
            pq.pop();
            long long val = top.first;
            int pos = top.second;
            
            ans += val;
            
            int l = L[pos];
            int r = R[pos];
            
            del[l] = true;
            del[r] = true;
            
            d[pos] = d[l] + d[r] - val;
            
            L[pos] = L[l];
            R[L[l]] = pos;
            R[pos] = R[r];
            L[R[r]] = pos;
            
            pq.push({d[pos], pos});
        }
        cout << ans << "\n";
    }
    return 0;
}
