#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C, D;
    while (cin >> R >> C >> D) {
        int K;
        cin >> K;
        vector<vector<int>> awake(R, vector<int>(C, 0));
        for (int i = 0; i < K; ++i) {
            int r, c;
            cin >> r >> c;
            awake[r][c]++;
        }
        
        int M;
        cin >> M;
        vector<vector<int>> ground(R, vector<int>(C, D));
        
        for (int i = 0; i < M; ++i) {
            int a, b, S, d;
            cin >> a >> b >> S >> d;
            int half = S / 2;
            int r_start = max(0, a - half);
            int r_end = min(R - 1, a + half);
            int c_start = max(0, b - half);
            int c_end = min(C - 1, b + half);
            
            bool has_awake = false;
            for (int r = r_start; r <= r_end; ++r) {
                for (int c = c_start; c <= c_end; ++c) {
                    if (awake[r][c] > 0) {
                        has_awake = true;
                        break;
                    }
                }
                if (has_awake) break;
            }
            
            if (has_awake) {
                for (int r = r_start; r <= r_end; ++r) {
                    for (int c = c_start; c <= c_end; ++c) {
                        awake[r][c] = 0;
                    }
                }
            } else {
                for (int r = r_start; r <= r_end; ++r) {
                    for (int c = c_start; c <= c_end; ++c) {
                        ground[r][c] -= d;
                    }
                }
            }
        }
        
        int max_h = -1e9;
        int min_h = 1e9;
        int awake_count = 0;
        
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (ground[r][c] > max_h) max_h = ground[r][c];
                if (ground[r][c] < min_h) min_h = ground[r][c];
                awake_count += awake[r][c];
            }
        }
        
        cout << max_h << " " << min_h << " " << awake_count << "\n";
    }
    
    return 0;
}
