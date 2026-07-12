#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        vector<int> b = a;
        sort(b.begin(), b.end());
        
        for (int i = 0; i < n; ++i) {
            cout << b[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";
        
        b.erase(unique(b.begin(), b.end()), b.end());
        int m = b.size();
        for (int i = m - 1; i >= 0; --i) {
            cout << b[i];
            if (i > 0) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
