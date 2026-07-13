#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    while (cin >> k) {
        int n[6];
        char letter[6][12];
        int score[6][12];
        
        for (int i = 0; i < k; i++) {
            cin >> n[i];
            for (int j = 0; j < n[i]; j++) {
                cin >> letter[i][j] >> score[i][j];
            }
        }
        
        int mult[6];
        int totalStates = 1;
        for (int i = 0; i < k; i++) {
            mult[i] = totalStates;
            totalStates *= (n[i] + 1);
        }
        
        vector<int> dp(totalStates, 0);
        
        for (int s = totalStates - 1; s >= 0; s--) {
            int p[6];
            int tmp = s;
            for (int i = 0; i < k; i++) {
                p[i] = tmp % (n[i] + 1);
                tmp /= (n[i] + 1);
            }
            
            int best = 0;
            for (int i = 0; i < k; i++) {
                if (p[i] >= n[i]) continue;
                for (int j = i + 1; j < k; j++) {
                    if (p[j] >= n[j]) continue;
                    if (letter[i][p[i]] == letter[j][p[j]]) {
                        int ns = s + mult[i] + mult[j];
                        int gain = score[i][p[i]] + score[j][p[j]] + dp[ns];
                        if (gain > best) best = gain;
                    }
                }
            }
            dp[s] = best;
        }
        
        cout << dp[0] << "\n";
    }
    return 0;
}
