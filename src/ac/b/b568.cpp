#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int M = 700000;
    string line;
    
    while (getline(cin, line)) {
        if (line.find("---") != string::npos) {
            cout << "\n------------------\n";
            continue;
        }
        
        stringstream ss(line);
        int n;
        if (!(ss >> n)) continue;
        
        getline(cin, line);
        stringstream ss2(line);
        vector<int> a;
        int x;
        while (ss2 >> x) a.push_back(x);
        
        bitset<700001> dp;
        dp[0] = 1;
        
        for (int v : a) {
            if (v <= 0) continue;
            // Non-wrapping: j+v <= M => dp << v
            // Wrapping: j+v > M => j+v-M => dp >> (M-v)
            dp = dp | (dp << v) | (dp >> (M - v));
        }
        
        int ans = 0;
        for (int i = M; i >= 0; i--) {
            if (dp[i]) { ans = i; break; }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
