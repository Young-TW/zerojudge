#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    bool first = true;
    while (cin >> N) {
        vector<int> S(N);
        for (int i = 0; i < N; i++) cin >> S[i];
        
        size_t total = (size_t)N * N * N;
        vector<long long> lhs;
        lhs.reserve(total);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                long long ab = (long long)S[i] * S[j];
                for (int k = 0; k < N; k++)
                    lhs.push_back(ab + S[k]);
            }
        sort(lhs.begin(), lhs.end());
        
        long long ans = 0;
        for (int d = 0; d < N; d++)
            for (int e = 0; e < N; e++)
                for (int f = 0; f < N; f++) {
                    long long val = (long long)S[d] * ((long long)S[e] + S[f]);
                    auto range = equal_range(lhs.begin(), lhs.end(), val);
                    ans += (range.second - range.first);
                }
        
        if (!first) cout << "\n";
        first = false;
        cout << ans << "\n";
    }
    return 0;
}
