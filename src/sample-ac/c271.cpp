#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
    long long w, s, l;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<Box> boxes(N);
        for (int i = 0; i < N; ++i) {
            cin >> boxes[i].w >> boxes[i].s >> boxes[i].l;
        }
        sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
            if (a.l != b.l) return a.l < b.l;
            if (a.s != b.s) return a.s < b.s;
            return a.w < b.w;
        });
        
        const long long INF = (long long)4e18;
        vector<long long> dp(N + 1, INF);
        dp[0] = 0;
        int max_h = 0;
        
        for (const auto& box : boxes) {
            for (int h = max_h; h >= 0; --h) {
                if (dp[h] != INF && dp[h] + box.w <= box.s) {
                    long long nw = dp[h] + box.w;
                    if (nw < dp[h + 1]) {
                        dp[h + 1] = nw;
                        if (h + 1 > max_h) max_h = h + 1;
                    }
                }
            }
        }
        cout << max_h << '\n';
    }
    return 0;
}
