#include <iostream>
#include <string>

using namespace std;

int LCP[1005][1005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K;
    string S;
    
    while (cin >> K >> S) {
        int N = S.length();
        
        for (int i = N; i >= 0; --i) {
            for (int j = N; j >= 0; --j) {
                if (i == N || j == N) {
                    LCP[i][j] = 0;
                } else if (S[i] == S[j]) {
                    LCP[i][j] = LCP[i + 1][j + 1] + 1;
                } else {
                    LCP[i][j] = 0;
                }
            }
        }
        
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + K + 1; j < N; ++j) {
                int L = j - i - K;
                if (LCP[i][j] >= L) {
                    ans++;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
