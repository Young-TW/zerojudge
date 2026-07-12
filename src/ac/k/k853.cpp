#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long K, N;
    while (cin >> K >> N) {
        vector<pair<long long, int>> events;
        events.reserve(2 * N);
        
        for (int i = 0; i < N; ++i) {
            long long L, R;
            cin >> L >> R;
            events.push_back({L, 1});
            events.push_back({R + 1, -1});
        }
        
        if (events.empty()) {
            cout << 0 << "\n";
            continue;
        }
        
        sort(events.begin(), events.end());
        
        long long ans = 0;
        long long current_overlap = 0;
        int i = 0;
        int M = events.size();
        
        while (i < M) {
            long long curr_time = events[i].first;
            
            while (i < M && events[i].first == curr_time) {
                current_overlap += events[i].second;
                i++;
            }
            
            if (i < M) {
                long long next_time = events[i].first;
                long long duration = next_time - curr_time;
                
                if (current_overlap > K) {
                    ans += K * duration;
                } else {
                    ans += current_overlap * duration;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
