#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> cnt(10, 0);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        vector<pair<int,int>> v;
        for (int d = 0; d < 10; d++)
            if (cnt[d] > 0) v.push_back({d, cnt[d]});
        sort(v.begin(), v.end(), [](const pair<int,int>&a, const pair<int,int>&b){
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
        for (size_t i = 0; i < v.size(); i++) {
            if (i) cout << ' ';
            cout << v[i].first;
        }
        cout << '\n';
    }
    return 0;
}
