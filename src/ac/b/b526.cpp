#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        int m;
        cin >> m;
        
        vector<pair<long long, int>> events;
        events.reserve(m * 2);
        
        for (int i = 0; i < m; ++i) {
            long long l, r;
            cin >> l >> r;
            events.emplace_back(l, 1);
            events.emplace_back(r + 1, -1);
        }
        
        sort(events.begin(), events.end());
        
        long long ans = 0;
        int cur = 0;
        long long last_pos = 1;
        
        for (const auto& e : events) {
            long long pos = e.first;
            int delta = e.second;
            if (pos > last_pos) {
                long long len = pos - last_pos;
                if (cur % 2 == 0) {
                    ans += len;
                }
            }
            cur += delta;
            last_pos = pos;
        }
        
        if (last_pos <= n) {
            long long len = n - last_pos + 1;
            if (cur % 2 == 0) {
                ans += len;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
