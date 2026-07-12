#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<pair<string, string>> foods(n);
        for (int i = 0; i < n; ++i) {
            cin >> foods[i].first >> foods[i].second;
        }
        
        string c;
        cin >> c;

        vector<string> ans;
        for (int i = 0; i < n; ++i) {
            if (foods[i].second == c) {
                ans.push_back(foods[i].first);
            }
        }

        if (ans.empty()) {
            cout << "No\n";
        } else {
            sort(ans.begin(), ans.end());
            for (size_t i = 0; i < ans.size(); ++i) {
                cout << ans[i] << "\n";
            }
        }
    }

    return 0;
}
