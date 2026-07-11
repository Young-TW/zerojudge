#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<pair<int, string>> v(n);
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            int j = s.size() - 1;
            while (j >= 0 && s[j] >= '0' && s[j] <= '9') {
                j--;
            }
            string name = s.substr(0, j + 1);
            int score = 0;
            int p = 1;
            for (int k = s.size() - 1; k > j; --k) {
                score += (s[k] - '0') * p;
                p *= 10;
            }
            v[i] = {score, name};
        }
        
        stable_sort(v.begin(), v.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
            return a.first > b.first;
        });
        
        int rank = 1;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && v[i].first != v[i-1].first) {
                rank++;
            }
            cout << rank << " " << v[i].second << " " << v[i].first << "\n";
        }
    }
    
    return 0;
}
