#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> sticks;
        int x;
        long long S = 0;
        while (iss >> x) {
            sticks.push_back(x);
            S += x;
        }
        if (sticks.empty()) continue;
        
        int half = S / 2;
        bitset<250005> dp;
        dp[0] = 1;
        for (int v : sticks) {
            if (v <= half)
                dp |= (dp << v);
        }
        
        long long ans = 0;
        for (int i = half; i >= 0; i--) {
            if (dp[i]) {
                ans = (long long)i * (S - i);
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
