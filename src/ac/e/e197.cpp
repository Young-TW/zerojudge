#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long N, M;
            cin >> N >> M;
            vector<long long> d(M), c(M);
            for (int i = 0; i < M; ++i) cin >> d[i];
            for (int i = 0; i < M; ++i) cin >> c[i];
            
            vector<pair<long long, long long>> v;
            for (int i = 0; i < M; ++i) {
                v.push_back({d[i], c[i]});
            }
            sort(v.begin(), v.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
                return a.first > b.first;
            });
            
            long long pos = 1;
            long long ans = 0;
            for (int i = 0; i < M; ++i) {
                long long di = v[i].first;
                long long ci = v[i].second;
                long long cnt;
                if (pos % 2 == 1) {
                    cnt = (ci + 1) / 2;
                } else {
                    cnt = ci / 2;
                }
                ans += cnt * di;
                pos += ci;
            }
            cout << ans * 2 << "\n";
        }
    }
    return 0;
}
