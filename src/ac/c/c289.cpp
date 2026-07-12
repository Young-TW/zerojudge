#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        vector<string> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        
        sort(v.begin(), v.end());
        
        int max_lcp = 0;
        for (int i = 0; i < n - 1; ++i) {
            int lcp = 0;
            int len = v[i].length();
            if (v[i+1].length() < len) {
                len = v[i+1].length();
            }
            while (lcp < len && v[i][lcp] == v[i+1][lcp]) {
                lcp++;
            }
            if (lcp > max_lcp) {
                max_lcp = lcp;
            }
        }
        
        cout << max_lcp << "\n";
    }
    
    return 0;
}
