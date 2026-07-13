#include <iostream>
#include <string>
#include <cstring>
using namespace std;

bool isVowel(char c) {
    return c=='A'||c=='E'||c=='I'||c=='O'||c=='U';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        int n = s.size();
        // dp[prev_type][run][hasL]
        // prev_type: 0=vowel, 1=consonant, 2=none(start)
        // run: 0=none, 1 or 2 consecutive of same type
        // hasL: 0 or 1
        long long dp[3][3][2];
        memset(dp, 0, sizeof(dp));
        dp[2][0][0] = 1;
        
        for (int i = 0; i < n; i++) {
            long long ndp[3][3][2];
            memset(ndp, 0, sizeof(ndp));
            
            for (int lt = 0; lt < 26; lt++) {
                char c = 'A' + lt;
                if (s[i] != '_' && s[i] != c) continue;
                
                int type = isVowel(c) ? 0 : 1;
                int hasL = (c == 'L') ? 1 : 0;
                
                for (int pt = 0; pt < 3; pt++) {
                    for (int run = 0; run < 3; run++) {
                        for (int hl = 0; hl < 2; hl++) {
                            if (dp[pt][run][hl] == 0) continue;
                            
                            int newRun;
                            if (pt == 2) {
                                newRun = 1;
                            } else if (pt == type) {
                                newRun = run + 1;
                                if (newRun > 2) continue;
                            } else {
                                newRun = 1;
                            }
                            
                            int newHl = hl | hasL;
                            ndp[type][newRun][newHl] += dp[pt][run][hl];
                        }
                    }
                }
            }
            
            memcpy(dp, ndp, sizeof(dp));
        }
        
        long long ans = 0;
        for (int pt = 0; pt < 3; pt++) {
            for (int run = 0; run < 3; run++) {
                ans += dp[pt][run][1];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
