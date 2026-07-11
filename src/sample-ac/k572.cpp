#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<pair<long long, long long>> events;
        events.reserve(2 * N);
        for (int i = 0; i < N; ++i) {
            long long L, R;
            cin >> L >> R;
            events.push_back({L, 1});
            events.push_back({R + 1, -1});
        }
        sort(events.begin(), events.end());
        
        long long current_cnt = 0;
        long long max_cnt = -1;
        long long best_T = 0;
        
        for (size_t i = 0; i < events.size(); ) {
            long long curr_x = events[i].first;
            long long delta = 0;
            while (i < events.size() && events[i].first == curr_x) {
                delta += events[i].second;
                i++;
            }
            current_cnt += delta;
            long long next_x = (i < events.size()) ? events[i].first : 3000000000LL;
            long long max_reachable = next_x - 1;
            
            if (current_cnt > max_cnt) {
                max_cnt = current_cnt;
                best_T = max_reachable;
            } else if (current_cnt == max_cnt) {
                if (max_reachable > best_T) {
                    best_T = max_reachable;
                }
            }
        }
        cout << best_T << "\n";
    }
    return 0;
}
