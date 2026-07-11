#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        unordered_map<int, vector<int>> pos;
        pos.reserve(n);
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            pos[x].push_back(i);
        }
        for (int i = 0; i < m; ++i) {
            int k, v;
            cin >> k >> v;
            auto it = pos.find(v);
            if (it != pos.end() && k <= it->second.size()) {
                cout << it->second[k - 1] << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    return 0;
}
