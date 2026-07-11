#include <iostream>

using namespace std;

int H, N;
int masks[4];
int ans = 0;

void dfs(int start, int depth, int curr_mask, int valid_trips) {
    if (depth == N) {
        int cnt = 0;
        for (int i = 0; i < 4; ++i) {
            if (valid_trips & (1 << i)) {
                cnt++;
            }
        }
        if (cnt >= H) {
            ans++;
        }
        return;
    }
    
    if (25 - start + 1 < N - depth) return;
    
    for (int i = start; i <= 25; ++i) {
        int next_mask = curr_mask | (1 << i);
        int next_valid = 0;
        int next_cnt = 0;
        for (int j = 0; j < 4; ++j) {
            if ((valid_trips & (1 << j)) && (next_mask & masks[j]) == next_mask) {
                next_valid |= (1 << j);
                next_cnt++;
            }
        }
        if (next_cnt >= H) {
            dfs(i + 1, depth + 1, next_mask, next_valid);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int sets[4][15] = {
        {1, 2, 3, 5, 6, 8, 11, 13, 17, 21, 22},
        {2, 3, 5, 7, 8, 13, 16, 17, 21, 22, 24},
        {1, 3, 5, 6, 7, 15, 16, 17, 22, 23, 24, 25},
        {2, 4, 5, 7, 8, 15, 17, 21, 23, 25}
    };
    int counts[4] = {11, 11, 12, 10};
    
    for (int i = 0; i < 4; ++i) {
        masks[i] = 0;
        for (int j = 0; j < counts[i]; ++j) {
            masks[i] |= (1 << sets[i][j]);
        }
    }
    
    while (cin >> H >> N) {
        ans = 0;
        dfs(1, 0, 0, 15);
        cout << ans << "\n";
    }
    
    return 0;
}
