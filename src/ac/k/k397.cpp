#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<pair<long long,long long>> rooms(N), meetings(M);
        for (int i = 0; i < N; i++) cin >> rooms[i].first >> rooms[i].second;
        for (int j = 0; j < M; j++) cin >> meetings[j].first >> meetings[j].second;
        long long t;
        cin >> t;
        
        vector<pair<long long,long long>> validRooms;
        vector<pair<long long,long long>> validMeetings;
        
        for (int i = 0; i < N; i++) {
            if (rooms[i].second - rooms[i].first >= t) {
                validRooms.push_back({rooms[i].first, rooms[i].second - t});
            }
        }
        for (int j = 0; j < M; j++) {
            if (meetings[j].second - meetings[j].first >= t) {
                validMeetings.push_back({meetings[j].first, meetings[j].second - t});
            }
        }
        
        long long ans = LLONG_MAX;
        
        if (!validRooms.empty() && !validMeetings.empty()) {
            sort(validRooms.begin(), validRooms.end());
            sort(validMeetings.begin(), validMeetings.end());
            int R = validRooms.size();
            
            // Case 1: start = c_j, need room with a_i <= c_j <= b_i - t
            {
                vector<long long> prefMaxR(R);
                prefMaxR[0] = validRooms[0].second;
                for (int i = 1; i < R; i++) {
                    prefMaxR[i] = max(prefMaxR[i-1], validRooms[i].second);
                }
                for (auto& m : validMeetings) {
                    long long c = m.first;
                    int idx = upper_bound(validRooms.begin(), validRooms.end(), make_pair(c, (long long)LLONG_MAX)) - validRooms.begin() - 1;
                    if (idx >= 0 && prefMaxR[idx] >= c) {
                        ans = min(ans, c);
                        break;
                    }
                }
            }
            
            // Case 2: start = a_i, need meeting with c_j < a_i <= d_j - t
            {
                int mIdx = 0;
                long long maxR = LLONG_MIN;
                for (auto& r : validRooms) {
                    long long a = r.first;
                    while (mIdx < (int)validMeetings.size() && validMeetings[mIdx].first < a) {
                        maxR = max(maxR, validMeetings[mIdx].second);
                        mIdx++;
                    }
                    if (maxR >= a) {
                        ans = min(ans, a);
                        break;
                    }
                }
            }
        }
        
        if (ans == LLONG_MAX) {
            cout << -1 << "\n";
        } else {
            cout << ans << " " << ans + t << "\n";
        }
    }
    return 0;
}
