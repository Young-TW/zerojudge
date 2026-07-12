#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long fact[21];
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) {
        fact[i] = fact[i - 1] * i;
    }
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            string s;
            unsigned long long k;
            if (!(cin >> s >> k)) break;
            
            int n = s.length();
            unsigned long long rem = k - 1;
            
            vector<int> avail(n);
            iota(avail.begin(), avail.end(), 0);
            
            vector<int> A(n);
            for (int i = 0; i < n; ++i) {
                int d = static_cast<int>(rem / fact[n - 1 - i]);
                rem %= fact[n - 1 - i];
                A[i] = avail[d];
                avail.erase(avail.begin() + d);
            }
            
            vector<pair<int, char>> v(n);
            for (int i = 0; i < n; ++i) {
                v[i] = make_pair(A[i], s[i]);
            }
            
            sort(v.begin(), v.end());
            
            string ans;
            for (int i = 0; i < n; ++i) {
                ans += v[i].second;
            }
            
            cout << "Case " << t << ": " << ans << "\n";
        }
    }
    
    return 0;
}
