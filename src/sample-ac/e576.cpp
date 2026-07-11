#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 1; t <= T; ++t) {
        if (t > 1) cout << "\n";
        
        int M;
        cin >> M;
        
        vector<pair<int, int>> segments;
        int L, R;
        while (cin >> L >> R) {
            if (L == 0 && R == 0) break;
            segments.push_back({L, R});
        }
        
        sort(segments.begin(), segments.end());
        
        vector<pair<int, int>> ans;
        int current_end = 0;
        int max_reach = 0;
        pair<int, int> best_segment;
        
        int i = 0;
        int n = segments.size();
        
        while (current_end < M) {
            max_reach = current_end;
            bool found = false;
            while (i < n && segments[i].first <= current_end) {
                if (segments[i].second > max_reach) {
                    max_reach = segments[i].second;
                    best_segment = segments[i];
                    found = true;
                }
                i++;
            }
            if (!found) {
                break;
            }
            ans.push_back(best_segment);
            current_end = max_reach;
        }
        
        if (current_end < M) {
            cout << "0\n";
        } else {
            cout << ans.size() << "\n";
            for (size_t j = 0; j < ans.size(); ++j) {
                cout << ans[j].first << " " << ans[j].second << "\n";
            }
        }
    }
    
    return 0;
}
