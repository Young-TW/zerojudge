#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> h(n), c(n);
        vector<int> idx(n);
        for (int i = 0; i < n; i++) {
            cin >> h[i] >> c[i];
            idx[i] = i;
        }
        
        // Sort by c[i]/h[i] increasing: a before b iff c[a]*h[b] < c[b]*h[a]
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            __int128 lhs = (__int128)c[a] * h[b];
            __int128 rhs = (__int128)c[b] * h[a];
            return lhs < rhs;
        });
        
        long long total = 0;
        long long sum_c = 0;
        for (int i = 0; i < n; i++) {
            int j = idx[i];
            sum_c += c[j];
            total += h[j] * sum_c;
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
