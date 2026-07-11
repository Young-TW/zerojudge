#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        vector<long long> x(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        long long k;
        cin >> k;
        
        vector<long long> S(n + 1);
        S[0] = 0;
        for (int i = 0; i < n; i++) S[i + 1] = S[i] + x[i];
        
        unordered_map<long long, int> next_min;
        next_min.reserve(n + 1);
        int best_i = -1, best_j = -1;
        
        for (int p = n; p >= 0; p--) {
            long long r = ((S[p] % k) + k) % k;
            auto it = next_min.find(r);
            if (it != next_min.end()) {
                best_i = p + 1;
                best_j = it->second;
            }
            next_min[r] = p;
        }
        
        if (best_i == -1) {
            cout << "no solutions.\n";
        } else {
            cout << best_i << " " << best_j << "\n";
        }
    }
    return 0;
}
