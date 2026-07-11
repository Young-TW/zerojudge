#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int getLCP(const string& a, const string& b) {
    int len = min(a.length(), b.length());
    int i = 0;
    while (i < len && a[i] == b[i]) {
        i++;
    }
    return i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<string> names(n);
            for (int i = 0; i < n; ++i) {
                cin >> names[i];
            }
            
            sort(names.begin(), names.end());
            
            long long total = 0;
            for (int i = 0; i < n; ++i) {
                int lcp_prev = 0;
                int lcp_next = 0;
                if (i > 0) {
                    lcp_prev = getLCP(names[i], names[i - 1]);
                }
                if (i < n - 1) {
                    lcp_next = getLCP(names[i], names[i + 1]);
                }
                int shortest = max(lcp_prev, lcp_next) + 1;
                total += shortest;
            }
            
            cout << total << "\n";
        }
    }
    
    return 0;
}
