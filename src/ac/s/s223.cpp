#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        vector<long long> d(n), h(n);
        for (int i = 0; i < n; ++i) cin >> d[i];
        for (int i = 0; i < n; ++i) cin >> h[i];
        
        vector<pair<long long, long long>> points(n);
        for (int i = 0; i < n; ++i) points[i] = {d[i], h[i]};
        sort(points.begin(), points.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
            return a.first < b.first;
        });
        
        vector<long long> C;
        C.reserve(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            long long dd = points[i+1].first - points[i].first;
            long long dh = points[i+1].second - points[i].second;
            long long cost = dd + max(0LL, 2 * dh);
            C.push_back(cost);
        }
        
        long long low = 0;
        long long high = accumulate(C.begin(), C.end(), 0LL);
        
        auto feasible = [&](long long X) -> bool {
            long long segments = 1;
            long long current = 0;
            for (long long c : C) {
                if (current + c <= X) {
                    current += c;
                } else {
                    ++segments;
                    current = 0;
                }
            }
            return segments <= k;
        };
        
        while (low < high) {
            long long mid = low + (high - low) / 2;
            if (feasible(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        cout << low << '\n';
    }
    
    return 0;
}
