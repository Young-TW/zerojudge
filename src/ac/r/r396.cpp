#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M;
    while (cin >> N >> M) {
        vector<pair<long long, long long>> first(N);
        for (long long i = 0; i < N; ++i) {
            cin >> first[i].first >> first[i].second;
        }
        vector<pair<long long, long long>> second(M);
        for (long long i = 0; i < M; ++i) {
            cin >> second[i].first >> second[i].second;
        }
        
        vector<pair<long long, long long>> poly;
        poly.reserve(N + M);
        for (auto &p : first) poly.push_back(p);
        for (long long i = M - 1; i >= 0; --i) poly.push_back(second[i]);
        
        long long sum = 0;
        long long sz = poly.size();
        for (long long i = 0; i < sz; ++i) {
            long long j = (i + 1) % sz;
            sum += poly[i].first * poly[j].second - poly[i].second * poly[j].first;
        }
        if (sum < 0) sum = -sum;
        cout << sum << '\n';
    }
    return 0;
}
