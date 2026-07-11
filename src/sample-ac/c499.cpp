#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string M, B;
    int T;
    
    while (cin >> M >> B >> T) {
        int n = M.size();
        int m = B.size();
        
        vector<int> dp(m + 1, 0);
        int max_len = 0;
        
        for (int i = 1; i <= n; ++i) {
            int prev = 0;
            for (int j = 1; j <= m; ++j) {
                int temp = dp[j];
                if (M[i - 1] == B[j - 1]) {
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
        
        if (max_len >= T) {
            cout << "kwa nini unaendesha\n";
        } else {
            cout << "sitini na tisa\n";
        }
    }
    
    return 0;
}
