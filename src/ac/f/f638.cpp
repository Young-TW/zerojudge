#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<long long> p(N + 1, 0);
        vector<long long> preP(N + 1, 0);
        vector<long long> preW(N + 1, 0);
        
        for (int i = 1; i <= N; ++i) {
            cin >> p[i];
            preP[i] = preP[i - 1] + p[i];
            preW[i] = preW[i - 1] + p[i] * i;
        }
        
        long long ans = 0;
        
        struct State {
            int s, t, level;
        };
        stack<State> st;
        st.push({1, N, 1});
        
        while (!st.empty()) {
            State curr = st.top();
            st.pop();
            
            int s = curr.s;
            int t = curr.t;
            int level = curr.level;
            
            if (level > K) continue;
            if (t - s + 1 < 3) continue;
            
            long long P = preP[t] - preP[s - 1];
            long long W = preW[t] - preW[s - 1];
            
            long long m = W / P;
            if (m < s + 1) m = s + 1;
            if (m > t - 1) m = t - 1;
            
            if (m + 1 <= t - 1) {
                long long val1 = W - m * P;
                long long val2 = W - (m + 1) * P;
                if (val1 < 0) val1 = -val1;
                if (val2 < 0) val2 = -val2;
                if (val2 < val1) {
                    m = m + 1;
                }
            }
            
            ans += p[m];
            
            st.push({s, m - 1, level + 1});
            st.push({m + 1, t, level + 1});
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
