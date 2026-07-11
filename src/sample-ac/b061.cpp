#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        vector<long long> nums;
        vector<char> ops;
        long long cur = 0;
        
        for (char c : s) {
            if (c >= '0' && c <= '9') {
                cur = cur * 10 + (c - '0');
            } else {
                nums.push_back(cur);
                ops.push_back(c);
                cur = 0;
            }
        }
        nums.push_back(cur);
        
        int n = nums.size();
        if (n == 0) continue;
        
        vector<vector<long long>> dp_max(n, vector<long long>(n, LLONG_MIN));
        vector<vector<long long>> dp_min(n, vector<long long>(n, LLONG_MAX));
        
        for (int i = 0; i < n; ++i) {
            dp_max[i][i] = nums[i];
            dp_min[i][i] = nums[i];
        }
        
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    char op = ops[k];
                    if (op == '+') {
                        dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k+1][j]);
                        dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k+1][j]);
                    } else if (op == '-') {
                        dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] - dp_min[k+1][j]);
                        dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] - dp_max[k+1][j]);
                    } else if (op == '*') {
                        long long v1 = dp_max[i][k] * dp_max[k+1][j];
                        long long v2 = dp_max[i][k] * dp_min[k+1][j];
                        long long v3 = dp_min[i][k] * dp_max[k+1][j];
                        long long v4 = dp_min[i][k] * dp_min[k+1][j];
                        dp_max[i][j] = max(dp_max[i][j], max(max(v1, v2), max(v3, v4)));
                        dp_min[i][j] = min(dp_min[i][j], min(min(v1, v2), min(v3, v4)));
                    }
                }
            }
        }
        
        cout << dp_max[0][n-1] << "\n";
    }
    
    return 0;
}
