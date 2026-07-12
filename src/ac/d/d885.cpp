#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        
        sort(v.begin(), v.end());
        
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && v[j] == v[i]) {
                ++j;
            }
            cout << v[i] << ' ' << (j - i) << '\n';
            i = j;
        }
    }
    
    return 0;
}
