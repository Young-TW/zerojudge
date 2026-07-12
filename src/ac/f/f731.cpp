#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<pair<int, int>> events;
        events.reserve(n * 2);
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            events.push_back({a, 1});
            events.push_back({b, -1});
        }
        
        sort(events.begin(), events.end());
        
        int current_viewers = 0;
        int max_viewers = 0;
        for (int i = 0; i < events.size(); ++i) {
            current_viewers += events[i].second;
            if (current_viewers > max_viewers) {
                max_viewers = current_viewers;
            }
        }
        
        cout << max_viewers << "\n";
    }
    
    return 0;
}
