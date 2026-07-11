#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int C;
    while (cin >> C) {
        for (int t = 1; t <= C; ++t) {
            string S, T;
            cin >> S >> T;
            
            int c10 = 0, c01 = 0, cq0 = 0, cq1 = 0;
            
            for (size_t i = 0; i < S.length(); ++i) {
                if (S[i] == '1' && T[i] == '0') c10++;
                else if (S[i] == '0' && T[i] == '1') c01++;
                else if (S[i] == '?' && T[i] == '0') cq0++;
                else if (S[i] == '?' && T[i] == '1') cq1++;
            }
            
            int ans;
            if (c10 > c01 + cq1) {
                ans = -1;
            } else if (c10 > c01) {
                ans = c10 + cq1 + cq0;
            } else {
                ans = c01 + cq1 + cq0;
            }
            
            cout << "Case " << t << ": " << ans << "\n";
        }
    }
    
    return 0;
}
