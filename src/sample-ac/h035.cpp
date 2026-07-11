#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        if (N == 0) {
            cout << "perfect\n";
            continue;
        }
        
        vector<long long> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }
        
        bool perfect = true;
        for (int i = 1; i < N; ++i) {
            if (a[i] <= a[i-1]) {
                perfect = false;
                break;
            }
        }
        
        if (perfect) {
            cout << "perfect\n";
            continue;
        }
        
        vector<long long> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int M = vals.size();
        
        vector<long long> bit(M + 1, LLONG_MIN / 2);
        
        auto update = [&](int idx, long long val) {
            for (; idx <= M; idx += idx & -idx) {
                bit[idx] = max(bit[idx], val);
            }
        };
        
        auto query = [&](int idx) {
            long long res = LLONG_MIN / 2;
            for (; idx > 0; idx -= idx & -idx) {
                res = max(res, bit[idx]);
            }
            return res;
        };
        
        long long ans = LLONG_MIN;
        for (int i = 0; i < N; ++i) {
            int rank = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
            long long prev_max = 0;
            if (rank > 1) {
                long long q = query(rank - 1);
                if (q > 0) {
                    prev_max = q;
                }
            }
            long long new_sum = a[i] + prev_max;
            update(rank, new_sum);
            if (new_sum > ans) {
                ans = new_sum;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
