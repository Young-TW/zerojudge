#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    while (cin >> n >> m >> q) {
        vector<bitset<1005>> groups(n + 1);
        for (int i = 1; i <= n; ++i) {
            int a;
            cin >> a;
            for (int j = 0; j < a; ++j) {
                int tip;
                cin >> tip;
                groups[i].set(tip);
            }
        }
        
        for (int i = 0; i < q; ++i) {
            int s, t;
            cin >> s >> t;
            int cnt_s = (groups[s] & ~groups[t]).count();
            int cnt_t = (groups[t] & ~groups[s]).count();
            cout << cnt_s * cnt_t << "\n";
        }
    }
    
    return 0;
}
