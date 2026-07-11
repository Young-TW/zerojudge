#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> evens;

void dfs(int val, int len) {
    if (len > 7) return;
    if (val > 0) evens.push_back(val);
    for (int d = 0; d <= 8; d += 2) {
        if (val == 0 && d == 0) continue;
        dfs(val * 10 + d, len + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    dfs(0, 0);
    sort(evens.begin(), evens.end());
    
    int n;
    while (cin >> n) {
        auto it = lower_bound(evens.begin(), evens.end(), n);
        int min_dist = 2000000;
        if (it != evens.end()) {
            min_dist = min(min_dist, *it - n);
        }
        if (it != evens.begin()) {
            --it;
            min_dist = min(min_dist, n - *it);
        }
        cout << min_dist << "\n";
    }
    return 0;
}
