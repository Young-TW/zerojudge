#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>

using namespace std;

double prob[4][4][4][4];

void precompute() {
    int atk_combinations[4] = {0, 6, 36, 216};
    int def_combinations[4] = {0, 6, 36, 216};

    for (int atk = 1; atk <= 3; ++atk) {
        for (int def = 1; def <= 3; ++def) {
            int total = atk_combinations[atk] * def_combinations[def];
            for (int i = 0; i < atk_combinations[atk]; ++i) {
                int a_dice[3] = {0};
                int tmp = i;
                for (int j = 0; j < atk; ++j) {
                    a_dice[j] = tmp % 6 + 1;
                    tmp /= 6;
                }
                sort(a_dice, a_dice + atk, greater<int>());
                for (int j = 0; j < def_combinations[def]; ++j) {
                    int d_dice[3] = {0};
                    tmp = j;
                    for (int k = 0; k < def; ++k) {
                        d_dice[k] = tmp % 6 + 1;
                        tmp /= 6;
                    }
                    sort(d_dice, d_dice + def, greater<int>());
                    
                    int loss_a = 0, loss_d = 0;
                    for (int k = 0; k < min(atk, def); ++k) {
                        if (a_dice[k] > d_dice[k]) loss_d++;
                        else loss_a++;
                    }
                    prob[atk][def][loss_a][loss_d] += 1.0;
                }
            }
            for (int la = 0; la <= 3; ++la) {
                for (int ld = 0; ld <= 3; ++ld) {
                    prob[atk][def][la][ld] /= total;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute();
    
    double dp[4][1005];
    for (int i = 0; i < 4; ++i) {
        for (int d = 0; d <= 1000; ++d) {
            dp[i][d] = (d == 0) ? 1.0 : 0.0;
        }
    }
    
    int ans[1005];
    memset(ans, 0, sizeof(ans));
    int found_count = 0;
    
    for (int a = 2; ; ++a) {
        int curr = a % 4;
        for (int d = 1; d <= 1000; ++d) {
            int atk = min(3, a - 1);
            int def = min(3, d);
            dp[curr][d] = 0;
            for (int la = 0; la <= 3; ++la) {
                for (int ld = 0; ld <= 3; ++ld) {
                    if (prob[atk][def][la][ld] > 0) {
                        int prev_a = a - la;
                        int prev_d = d - ld;
                        int prev_curr = prev_a % 4;
                        dp[curr][d] += prob[atk][def][la][ld] * dp[prev_curr][prev_d];
                    }
                }
            }
            if (dp[curr][d] > 0.5 && ans[d] == 0) {
                ans[d] = a;
                found_count++;
            }
        }
        if (found_count == 1000) break;
    }
    
    int x;
    while (cin >> x && x != 0) {
        cout << ans[x] << "\n";
    }
    
    return 0;
}
