#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        int m;
        if (!(cin >> m)) break;
        vector<pair<long long, long long>> items(m);
        for (int i = 0; i < m; ++i) {
            cin >> items[i].first >> items[i].second;
        }
        
        sort(items.begin(), items.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
            return a.second > b.second;
        });
        
        long long total_value = 0;
        for (int i = 0; i < m && n > 0; ++i) {
            long long take = min(items[i].first, n);
            total_value += take * items[i].second;
            n -= take;
        }
        
        cout << total_value << "\n";
    }
    
    return 0;
}
