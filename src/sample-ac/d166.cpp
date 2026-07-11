#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> b;
        int x;
        while (ss >> x) {
            if (x == -1) return 0;
            b.push_back(x);
        }
        if (b.empty()) continue;
        int m = b.size();
        vector<int> ans;
        for (int k = m; k >= 1; --k) {
            ans.insert(ans.begin() + b[k - 1], k);
        }
        for (int i = 0; i < m; ++i) {
            cout << ans[i] << (i == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
