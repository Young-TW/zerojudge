#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M;
    while (cin >> N >> M) {
        vector<long long> ids;
        ids.reserve(N);
        vector<long long> a(N), b(N);
        vector<long long> coords;
        coords.reserve(3 * N);
        
        for (long long i = 0; i < N; ++i) {
            long long v, ai, bi;
            cin >> v >> ai >> bi;
            ids.push_back(v);
            a[i] = ai;
            b[i] = bi;
            coords.push_back(ai);
            coords.push_back(bi + 1);
            coords.push_back(v);
        }
        
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        
        vector<long long> diff(coords.size() + 1, 0);
        
        for (long long i = 0; i < N; ++i) {
            long long v = ids[i];
            long long ai = a[i];
            long long bi = b[i];
            size_t idx_a = lower_bound(coords.begin(), coords.end(), ai) - coords.begin();
            size_t idx_b1 = lower_bound(coords.begin(), coords.end(), bi + 1) - coords.begin();
            diff[idx_a] += v;
            diff[idx_b1] -= v;
        }
        
        for (size_t i = 1; i < coords.size(); ++i) {
            diff[i] += diff[i - 1];
        }
        
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());
        
        long long best_id = -1;
        long long max_sum = -1;
        
        for (long long id : ids) {
            size_t idx = lower_bound(coords.begin(), coords.end(), id) - coords.begin();
            long long sum = diff[idx];
            if (sum > max_sum || (sum == max_sum && id < best_id)) {
                max_sum = sum;
                best_id = id;
            }
        }
        
        cout << best_id << ' ' << max_sum << '\n';
    }
    
    return 0;
}
