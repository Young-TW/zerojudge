#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            int n = s.length();
            
            if (n == 0) {
                cout << 0 << "\n";
                continue;
            }
            
            int dp[5005] = {0};
            int max_len = 0;
            
            for (int i = 0; i < n; ++i) {
                int prev = 0;
                for (int j = 0; j < n; ++j) {
                    int temp = dp[j];
                    if (i != j && s[i] == s[j]) {
                        dp[j] = prev + 1;
                        if (dp[j] > max_len) {
                            max_len = dp[j];
                        }
                    } else {
                        dp[j] = 0;
                    }
                    prev = temp;
                }
            }
            
            cout << max_len << "\n";
        }
    }
    
    return 0;
}
