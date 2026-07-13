#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <algorithm>

using namespace std;

struct Transition {
    uint16_t new1, new2, new3;
    uint8_t cnt;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> blocked(n + 3, 0);
        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            blocked[x - 1] |= (1 << (y - 1));
        }
        int full_mask = (1 << m) - 1;
        for (int i = n; i < n + 3; ++i) blocked[i] = full_mask;

        unordered_map<uint32_t, int> dp, next_dp;
        dp.reserve(10000);
        next_dp.reserve(10000);
        dp[0] = 0;

        unordered_map<uint32_t, vector<Transition>> trans_cache;
        trans_cache.reserve(10000);

        function<void(int, int, int, int, int, int, int, int, vector<Transition>&)> dfs = 
        [&](int col, int free1, int free2, int free3, int cur_new1, int cur_new2, int cur_new3, int cnt, vector<Transition>& result) {
            while (col < m) {
                if ((free1 & (1 << col)) && !(cur_new1 & (1 << col))) break;
                col++;
            }
            if (col == m) {
                result.push_back({static_cast<uint16_t>(cur_new1), static_cast<uint16_t>(cur_new2), static_cast<uint16_t>(cur_new3), static_cast<uint8_t>(cnt)});
                return;
            }
            // Option 1: skip this column
            dfs(col + 1, free1, free2, free3, cur_new1, cur_new2, cur_new3, cnt, result);
            // Option 2: place 2x3 horizontal
            if (col + 2 < m) {
                int bits = (1 << col) | (1 << (col + 1)) | (1 << (col + 2));
                if ((free1 & bits) == bits && (free2 & bits) == bits &&
                    (cur_new1 & bits) == 0 && (cur_new2 & bits) == 0) {
                    dfs(col + 3, free1, free2, free3, cur_new1 | bits, cur_new2 | bits, cur_new3, cnt + 1, result);
                }
            }
            // Option 3: place 3x2 vertical
            if (col + 1 < m) {
                int bits = (1 << col) | (1 << (col + 1));
                if ((free1 & bits) == bits && (free2 & bits) == bits && (free3 & bits) == bits &&
                    (cur_new1 & bits) == 0 && (cur_new2 & bits) == 0 && (cur_new3 & bits) == 0) {
                    dfs(col + 2, free1, free2, free3, cur_new1 | bits, cur_new2 | bits, cur_new3 | bits, cnt + 1, result);
                }
            }
        };

        auto get_transitions = [&](int free1, int free2, int free3) -> const vector<Transition>& {
            uint32_t key = static_cast<uint32_t>(free1) | (static_cast<uint32_t>(free2) << 10) | (static_cast<uint32_t>(free3) << 20);
            auto it = trans_cache.find(key);
            if (it != trans_cache.end()) return it->second;
            vector<Transition> trans_vec;
            dfs(0, free1, free2, free3, 0, 0, 0, 0, trans_vec);
            auto insert_result = trans_cache.emplace(key, std::move(trans_vec));
            return insert_result.first->second;
        };

        for (int i = 0; i < n; ++i) {
            int b1 = blocked[i];
            int b2 = blocked[i + 1];
            int b3 = blocked[i + 2];
            next_dp.clear();
            for (const auto& entry : dp) {
                uint32_t state_key = entry.first;
                int val = entry.second;
                int mask1 = state_key & full_mask;
                int mask2 = (state_key >> 10) & full_mask;
                if (mask1 & b1) continue;
                if (mask2 & b2) continue;
                int free1 = (~(mask1 | b1)) & full_mask;
                int free2 = (~(mask2 | b2)) & full_mask;
                int free3 = (~b3) & full_mask;
                const vector<Transition>& trans = get_transitions(free1, free2, free3);
                for (const Transition& t : trans) {
                    int next_mask1 = mask2 | t.new2;
                    int next_mask2 = t.new3;
                    uint32_t next_key = static_cast<uint32_t>(next_mask1) | (static_cast<uint32_t>(next_mask2) << 10);
                    auto it = next_dp.find(next_key);
                    if (it == next_dp.end()) {
                        next_dp.emplace(next_key, val + t.cnt);
                    } else {
                        it->second = max(it->second, val + t.cnt);
                    }
                }
            }
            dp.swap(next_dp);
        }

        int ans = 0;
        for (const auto& entry : dp) {
            ans = max(ans, entry.second);
        }
        cout << ans << '\n';
    }
    return 0;
}
