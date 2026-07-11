#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int t = 0; t < N; ++t) {
            string s;
            cin >> s;
            
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
            vector<vector<long long>> dp_max(n, vector<long long>(n, 0));
            vector<vector<long long>> dp_min(n, vector<long long>(n, 0));
            
            for (int i = 0; i < n; ++i) {
                dp_max[i][i] = nums[i];
                dp_min[i][i] = nums[i];
            }
            
            for (int len = 2; len <= n; ++len) {
                for (int i = 0; i <= n - len; ++i) {
                    int j = i + len - 1;
                    dp_max[i][j] = -1;
                    dp_min[i][j] = 1e18;
                    
                    for (int k = i; k < j; ++k) {
                        char op = ops[k];
                        if (op == '+') {
                            dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k+1][j]);
                            dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k+1][j]);
                        } else if (op == '*') {
                            dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] * dp_max[k+1][j]);
                            dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] * dp_min[k+1][j]);
                        }
                    }
                }
            }
            
            cout << "The maximum and minimum are " << dp_max[0][n-1] << " and " << dp_min[0][n-1] << ".\n";
        }
    }
    
    return 0;
}
