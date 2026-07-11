#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    long long M;
    while (cin >> N >> M >> K) {
        vector<int> bit(N + 1);
        for (int i = 1; i <= N; i++) {
            bit[i] = i & -i;
        }
        
        int bit_mask = 1;
        while (bit_mask <= N) bit_mask <<= 1;
        bit_mask >>= 1;
        
        auto find_kth = [&](int k) -> int {
            int idx = 0;
            for (int step = bit_mask; step > 0; step >>= 1) {
                if (idx + step <= N && bit[idx + step] < k) {
                    idx += step;
                    k -= bit[idx];
                }
            }
            return idx + 1;
        };
        
        auto update = [&](int p, int val) {
            for (int i = p; i <= N; i += i & -i) {
                bit[i] += val;
            }
        };
        
        int cnt = N, rank = 1, ans = 0;
        for (int i = 1; i <= K; i++) {
            int target = (rank + M - 2) % cnt + 1;
            int pos = find_kth(target);
            if (i == K) {
                int next_target = (target < cnt) ? target + 1 : 1;
                ans = find_kth(next_target);
                break;
            }
            update(pos, -1);
            cnt--;
            rank = (target <= cnt) ? target : 1;
        }
        cout << ans << "\n";
    }
    return 0;
}
