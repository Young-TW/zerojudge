#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int happy[10005][32];
int dp[2][16];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, C;
    bool first_case = true;
    while (cin >> N >> C) {
        memset(happy, 0, sizeof(int) * N * 32);
        
        for (int i = 0; i < C; ++i) {
            int E, F, L;
            cin >> E >> F >> L;
            int E0 = E - 1;
            int fear_mask = 0;
            int like_mask = 0;
            for (int j = 0; j < F; ++j) {
                int X;
                cin >> X;
                int offset = (X - 1 - E0 + N) % N;
                fear_mask |= (1 << offset);
            }
            for (int j = 0; j < L; ++j) {
                int Y;
                cin >> Y;
                int offset = (Y - 1 - E0 + N) % N;
                like_mask |= (1 << offset);
            }
            for (int mask = 0; mask < 32; ++mask) {
                if ((mask & fear_mask) != 0 || (~mask & like_mask) != 0) {
                    happy[E0][mask]++;
                }
            }
        }
        
        int ans = 0;
        for (int init_mask = 0; init_mask < 16; ++init_mask) {
            memset(dp, -1, sizeof(dp));
            dp[1][init_mask] = 0;
            
            for (int i = 4; i < N; ++i) {
                int curr = i % 2;
                int prev = 1 - curr;
                for (int j = 0; j < 16; ++j) {
                    dp[curr][j] = -1;
                }
                
                for (int old_S = 0; old_S < 16; ++old_S) {
                    if (dp[prev][old_S] != -1) {
                        for (int bit = 0; bit < 2; ++bit) {
                            int new_S = ((old_S >> 1) & 7) | (bit << 3);
                            int mask = old_S | (bit << 4);
                            int val = dp[prev][old_S] + happy[i - 4][mask];
                            if (val > dp[curr][new_S]) {
                                dp[curr][new_S] = val;
                            }
                        }
                    }
                }
            }
            
            int curr = (N - 1) % 2;
            for (int final_S = 0; final_S < 16; ++final_S) {
                if (dp[curr][final_S] != -1) {
                    int mask1 = final_S | ((init_mask & 1) << 4);
                    int mask2 = ((final_S >> 1) & 7) | ((init_mask & 3) << 3);
                    int mask3 = ((final_S >> 2) & 3) | ((init_mask & 7) << 2);
                    int mask4 = ((final_S >> 3) & 1) | (init_mask << 1);
                    
                    int total = dp[curr][final_S] + happy[N - 4][mask1] + happy[N - 3][mask2] + happy[N - 2][mask3] + happy[N - 1][mask4];
                    if (total > ans) {
                        ans = total;
                    }
                }
            }
        }
        
        if (!first_case) cout << "\n";
        first_case = false;
        cout << ans << "\n";
    }
    
    return 0;
}
