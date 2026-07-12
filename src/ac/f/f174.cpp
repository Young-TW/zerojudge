#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<long long> P(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int x;
            cin >> x;
            P[i] = P[i - 1] + x;
        }
        
        deque<int> dq;
        dq.push_back(0);
        long long ans = 0;
        
        for (int i = 1; i <= N; ++i) {
            while (!dq.empty() && dq.front() < i - K) {
                dq.pop_front();
            }
            
            if (!dq.empty()) {
                ans = max(ans, P[i] - P[dq.front()]);
            }
            
            while (!dq.empty() && P[dq.back()] >= P[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
