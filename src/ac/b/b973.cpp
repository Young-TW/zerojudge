#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, t;
    while (cin >> n >> t) {
        vector<int> times(t, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < t; ++j) {
                int m, s;
                char c;
                cin >> m >> c >> s;
                times[j] += m * 60 + s;
            }
        }
        vector<pair<int, int>> teams(t);
        for (int j = 0; j < t; ++j) {
            teams[j] = {times[j], j + 1};
        }
        sort(teams.begin(), teams.end());
        for (int j = 0; j < t; ++j) {
            cout << teams[j].second << " " << teams[j].first << "\n";
        }
    }
    
    return 0;
}
