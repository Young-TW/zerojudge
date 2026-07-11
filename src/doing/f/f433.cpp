#include <iostream>
#include <cstring>

using namespace std;

int H, K;
int best_ans;
int best_stamps[10];
int current_stamps[10];

const int MAX_VAL = 4000;
int dp[MAX_VAL];

void dfs(int idx, int last_val, int current_max_cont) {
    if (idx == K) {
        if (current_max_cont > best_ans) {
            best_ans = current_max_cont;
            memcpy(best_stamps, current_stamps, sizeof(current_stamps));
        }
        return;
    }

    int rem = K - idx;
    long long upper_bound = current_max_cont;
    for (int i = 0; i < rem; ++i) {
        upper_bound *= (H + 1);
        if (upper_bound > MAX_VAL) {
            upper_bound = MAX_VAL;
            break;
        }
    }
    if (upper_bound <= best_ans) {
        return;
    }

    for (int next_val = current_max_cont + 1; next_val > last_val; --next_val) {
        int new_dp[MAX_VAL];
        memcpy(new_dp, dp, sizeof(new_dp));
        
        for (int i = 0; i + next_val < MAX_VAL; ++i) {
            if (new_dp[i] < H) {
                if (new_dp[i + next_val] > new_dp[i] + 1) {
                    new_dp[i + next_val] = new_dp[i] + 1;
                }
            }
        }
        
        int new_max_cont = current_max_cont;
        while (new_max_cont + 1 < MAX_VAL && new_dp[new_max_cont + 1] <= H) {
            new_max_cont++;
        }
        
        current_stamps[idx] = next_val;
        dfs(idx + 1, next_val, new_max_cont);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> H >> K && (H || K)) {
        best_ans = 0;
        memset(best_stamps, 0, sizeof(best_stamps));
        
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i <= H; ++i) {
            dp[i] = i;
        }
        current_stamps[0] = 1;
        
        dfs(1, 1, H);
        
        for (int i = 0; i < K; ++i) {
            cout << best_stamps[i] << " ";
        }
        cout << "-> " << best_ans << "\n";
    }
    
    return 0;
}
