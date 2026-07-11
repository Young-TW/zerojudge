#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, S, N;
    while (cin >> M >> S >> N) {
        vector<int> x(N);
        int total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
            total += x[i];
        }
        
        vector<char> dp(M + 1, 0);
        dp[0] = 1;
        
        for (int i = 0; i < N; ++i) {
            if (x[i] > 0) {
                for (int j = M; j >= x[i]; --j) {
                    if (dp[j - x[i]]) {
                        dp[j] = 1;
                    }
                }
            }
        }
        
        for (int j = S; j <= M; ++j) {
            if (dp[j]) {
                cout << j << "\n";
                break;
            }
        }
    }
    
    return 0;
}
