#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> parent;

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        vector<pair<int,int>> mines(c);
        unordered_map<long long, int> mp;
        mp.reserve(c * 2 + 1);
        
        for (int i = 0; i < c; i++) {
            cin >> mines[i].first >> mines[i].second;
            mp[(long long)mines[i].first * 100001LL + mines[i].second] = i;
        }
        
        parent.resize(c);
        for (int i = 0; i < c; i++) parent[i] = i;
        
        for (int i = 0; i < c; i++) {
            int r = mines[i].first, col = mines[i].second;
            for (int dr = -2; dr <= 2; dr++) {
                for (int dc = -2; dc <= 2; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr, nc = col + dc;
                    auto it = mp.find((long long)nr * 100001LL + nc);
                    if (it != mp.end()) {
                        int j = it->second;
                        int pi = find(i), pj = find(j);
                        if (pi != pj) parent[pi] = pj;
                    }
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < c; i++) {
            if (find(i) == i) ans++;
        }
        cout << ans << "\n";
    }
    return 0;
}
