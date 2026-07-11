#include <iostream>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        multiset<long long> st[8];
        int cnt = 0;
        
        for (int i = 0; i < n; ++i) {
            int ty;
            long long x, y, z;
            cin >> ty >> x >> y >> z;
            
            long long vals[8] = {
                x + y + z,
                x + y - z,
                x - y + z,
                x - y - z,
                -x + y + z,
                -x + y - z,
                -x - y + z,
                -x - y - z
            };
            
            if (ty == 1) {
                for (int j = 0; j < 8; ++j) {
                    st[j].insert(vals[j]);
                }
                cnt++;
            } else {
                for (int j = 0; j < 8; ++j) {
                    st[j].erase(st[j].find(vals[j]));
                }
                cnt--;
            }
            
            if (cnt < 2) {
                cout << -1 << "\n";
            } else {
                long long ans = 0;
                for (int j = 0; j < 8; ++j) {
                    long long diff = *st[j].rbegin() - *st[j].begin();
                    if (diff > ans) ans = diff;
                }
                cout << ans << "\n";
            }
        }
    }
    
    return 0;
}
