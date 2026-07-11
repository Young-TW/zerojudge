#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long U;
    while (cin >> N >> U) {
        vector<int> sum((N + 1) * (N + 1), 0);
        vector<int> max_sq_prev(N, 0);
        vector<int> max_sq_curr(N, 0);

        int best = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int val;
                cin >> val;
                
                int cost = (val == -1) ? 0 : val;
                int idx = (i + 1) * (N + 1) + (j + 1);
                int idx_up = i * (N + 1) + (j + 1);
                int idx_left = (i + 1) * (N + 1) + j;
                int idx_up_left = i * (N + 1) + j;
                sum[idx] = sum[idx_up] + sum[idx_left] - sum[idx_up_left] + cost;

                if (val == -1) {
                    max_sq_curr[j] = 0;
                } else {
                    if (i == 0 || j == 0) {
                        max_sq_curr[j] = 1;
                    } else {
                        max_sq_curr[j] = min({max_sq_prev[j], max_sq_curr[j-1], max_sq_prev[j-1]}) + 1;
                    }
                }

                while (best < max_sq_curr[j]) {
                    int L = best + 1;
                    int r1 = i - L + 1;
                    int c1 = j - L + 1;
                    int r2 = i;
                    int c2 = j;
                    
                    int idx1 = (r2 + 1) * (N + 1) + (c2 + 1);
                    int idx2 = r1 * (N + 1) + (c2 + 1);
                    int idx3 = (r2 + 1) * (N + 1) + c1;
                    int idx4 = r1 * (N + 1) + c1;
                    
                    long long current_sum = sum[idx1] - sum[idx2] - sum[idx3] + sum[idx4];
                    
                    if (current_sum <= U) {
                        best++;
                    } else {
                        break;
                    }
                }
            }
            swap(max_sq_prev, max_sq_curr);
        }

        cout << (long long)best * best << "\n";
    }

    return 0;
}
