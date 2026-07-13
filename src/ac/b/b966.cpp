#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<pair<int, int>> segments(N);
        for (int i = 0; i < N; ++i) {
            cin >> segments[i].first >> segments[i].second;
        }
        
        sort(segments.begin(), segments.end());
        
        long long total_length = 0;
        if (N > 0) {
            int cur_L = segments[0].first;
            int cur_R = segments[0].second;
            for (int i = 1; i < N; ++i) {
                if (segments[i].first > cur_R) {
                    total_length += (cur_R - cur_L);
                    cur_L = segments[i].first;
                    cur_R = segments[i].second;
                } else {
                    if (segments[i].second > cur_R) {
                        cur_R = segments[i].second;
                    }
                }
            }
            total_length += (cur_R - cur_L);
        }
        
        cout << total_length << "\n";
    }
    
    return 0;
}
