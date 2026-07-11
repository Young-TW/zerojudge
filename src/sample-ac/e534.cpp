#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w, h;
    while (cin >> w >> h) {
        vector<pair<int, int>> v(6);
        v[0] = {min(w, h), max(w, h)};
        for (int i = 1; i < 6; ++i) {
            if (!(cin >> w >> h)) return 0;
            v[i] = {min(w, h), max(w, h)};
        }
        
        sort(v.begin(), v.end());
        
        bool ok = true;
        if (v[0].first != v[1].first || v[0].second != v[1].second) ok = false;
        if (v[2].first != v[3].first || v[2].second != v[3].second) ok = false;
        if (v[4].first != v[5].first || v[4].second != v[5].second) ok = false;
        
        if (v[0].first != v[2].first) ok = false;
        if (v[0].second != v[4].first) ok = false;
        if (v[2].second != v[4].second) ok = false;
        
        if (ok) {
            cout << "POSSIBLE\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
    
    return 0;
}
