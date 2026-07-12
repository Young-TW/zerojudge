#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        while (n--) {
            vector<pair<int, int>> activities;
            int s, f;
            while (cin >> s >> f) {
                if (s == 0 && f == 0) break;
                activities.push_back({s, f});
            }
            
            sort(activities.begin(), activities.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
                if (a.second != b.second) return a.second < b.second;
                return a.first < b.first;
            });
            
            int count = 0;
            int last_end = 0;
            for (const auto& act : activities) {
                if (act.first >= last_end) {
                    count++;
                    last_end = act.second;
                }
            }
            cout << count << "\n";
        }
    }
    return 0;
}
