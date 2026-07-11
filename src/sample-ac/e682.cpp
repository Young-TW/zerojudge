#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string word;
    while (cin >> word) {
        vector<string> A, B;
        if (word != "#") {
            A.push_back(word);
            while (cin >> word && word != "#") {
                A.push_back(word);
            }
        }
        
        while (cin >> word && word != "#") {
            B.push_back(word);
        }
        
        int n = A.size();
        int m = B.size();
        int dp[105][105] = {0};
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (A[i-1] == B[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        vector<string> lcs;
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (A[i-1] == B[j-1]) {
                lcs.push_back(A[i-1]);
                i--;
                j--;
            } else if (dp[i-1][j] > dp[i][j-1]) {
                i--;
            } else {
                j--;
            }
        }
        
        reverse(lcs.begin(), lcs.end());
        
        for (size_t k = 0; k < lcs.size(); ++k) {
            if (k > 0) cout << " ";
            cout << lcs[k];
        }
        cout << "\n";
    }
    
    return 0;
}
