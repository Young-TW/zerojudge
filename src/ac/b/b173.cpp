#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool check(const vector<int>& pos, int L, int D, int K) {
    int target = pos[0] + L - D;
    int n = pos.size();
    int count = 1;
    int cur_idx = 0;
    int cur_pos = pos[0];
    if (cur_pos >= target) return count <= K;
    int j = 1;
    while (cur_pos < target) {
        while (j < n && pos[j] <= cur_pos + D) {
            j++;
        }
        if (j - 1 == cur_idx) {
            return false;
        }
        cur_idx = j - 1;
        cur_pos = pos[cur_idx];
        count++;
        if (count > K) return false;
    }
    return count <= K;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
        }
        int mid = N / 2;
        int L = 2 * N;
        for (int orbit = 0; orbit < M; ++orbit) {
            vector<int> allowed;
            allowed.reserve(L);
            // East column: top to bottom
            for (int row = 0; row < N; ++row) {
                if (grid[row][orbit] == '1') {
                    allowed.push_back(row);
                }
            }
            // West column: bottom to top
            for (int row = N - 1; row >= 0; --row) {
                if (grid[row][orbit + M] == '1') {
                    allowed.push_back(N + (N - 1 - row));
                }
            }
            sort(allowed.begin(), allowed.end());
            int p0 = mid;
            // Build linearized positions (sorted)
            vector<int> pos;
            pos.reserve(allowed.size());
            for (int a : allowed) {
                if (a >= p0) pos.push_back(a);
            }
            for (int a : allowed) {
                if (a < p0) pos.push_back(a + L);
            }
            // Binary search for minimum R
            int low = 0, high = (N - 1) / 2;
            int ans = high;
            while (low <= high) {
                int midR = (low + high) / 2;
                int D = 2 * midR + 1;
                if (check(pos, L, D, K)) {
                    ans = midR;
                    high = midR - 1;
                } else {
                    low = midR + 1;
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
