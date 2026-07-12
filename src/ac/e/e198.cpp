#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N;
        long long K, X;
        cin >> N >> K >> X;
        
        priority_queue<long long, vector<long long>, greater<long long>> pq1;
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq2;
        
        pq2.push({K, 0});
        
        long long S = 0;
        long long dp = 0;
        
        for (int i = 1; i <= N; ++i) {
            long long p;
            cin >> p;
            S += p;
            
            while (!pq2.empty() && pq2.top().first <= S) {
                auto p_top = pq2.top();
                pq2.pop();
                long long S_j = p_top.first - K;
                long long val = p_top.second - 2 * S_j;
                pq1.push(val);
            }
            
            long long val1 = 1000000000000000000LL;
            long long val2 = 1000000000000000000LL;
            if (!pq1.empty()) {
                val1 = pq1.top() + S - K;
            }
            if (!pq2.empty()) {
                val2 = pq2.top().second + K - S;
            }
            
            dp = X + min(val1, val2);
            pq2.push({S + K, dp + S});
        }
        
        cout << dp << "\n";
    }
    
    return 0;
}
