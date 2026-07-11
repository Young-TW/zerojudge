#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> nums;
        int x;
        int total = 0;
        while (ss >> x) {
            nums.push_back(x);
            total += x;
        }
        if (nums.empty()) continue;
        
        bitset<60005> dp;
        dp[0] = 1;
        for (int num : nums) {
            dp |= (dp << num);
        }
        
        int half = total / 2;
        for (int i = half; i >= 0; --i) {
            if (dp[i]) {
                cout << i * (total - i) << "\n";
                break;
            }
        }
    }
    return 0;
}
