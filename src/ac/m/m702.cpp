#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        map<string, int> votes;
        for (int i = 0; i < n; ++i) {
            string name;
            cin >> name;
            votes[name]++;
        }
        
        vector<pair<string, int>> v(votes.begin(), votes.end());
        sort(v.begin(), v.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
        
        for (int i = 0; i < m; ++i) {
            if (i > 0) cout << " ";
            cout << v[i].first;
        }
        cout << "\n";
    }
    return 0;
}
