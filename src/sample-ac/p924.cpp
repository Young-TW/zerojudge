#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << '\n';
            continue;
        }
        
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        vector<int> res;
        int cnt = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] == a[i - 1]) {
                cnt++;
            } else {
                res.push_back(cnt);
                cnt = 1;
            }
        }
        res.push_back(cnt);
        
        for (size_t i = 0; i < res.size(); ++i) {
            cout << res[i] << (i + 1 == res.size() ? '\n' : ' ');
        }
    }
    
    return 0;
}
