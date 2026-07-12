#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        vector<int> bit(n + 1, 0);
        
        auto add = [&](int i, int delta) {
            for (; i <= n; i += i & -i) {
                bit[i] += delta;
            }
        };
        
        auto sum = [&](int i) {
            int s = 0;
            for (; i > 0; i -= i & -i) {
                s += bit[i];
            }
            return s;
        };
        
        long long inv_count = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            inv_count += (long long)i - sum(x);
            add(x, 1);
        }
        
        if (inv_count % 2 == 1) {
            cout << "Marcelo\n";
        } else {
            cout << "Carlos\n";
        }
    }
    
    return 0;
}
