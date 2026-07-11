#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M;
    while (cin >> N >> M) {
        int K;
        cin >> K;
        vector<pair<long long, long long>> upgrades;
        upgrades.reserve(K);
        for (int i = 0; i < K; ++i) {
            long long a, b;
            cin >> a >> b;
            upgrades.emplace_back(a, b);
        }
        
        sort(upgrades.begin(), upgrades.end(),
             [](const pair<long long, long long>& lhs, const pair<long long, long long>& rhs) {
                 return lhs.first < rhs.first;
             });
        
        priority_queue<long long> pq; // max-heap for gains
        long long level = 1;          // initial level
        int idx = 0;
        long long used = 0;
        
        while (used < M) {
            while (idx < K && upgrades[idx].first <= level) {
                pq.push(upgrades[idx].second);
                ++idx;
            }
            if (pq.empty()) break;
            
            level += pq.top();
            pq.pop();
            ++used;
            
            if (level >= N) break;
        }
        
        cout << (level >= N ? 1 : 0) << '\n';
    }
    return 0;
}
