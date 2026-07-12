#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<tuple<long long, long long, long long>> programs(n);
    for (int i = 0; i < n; ++i) {
        long long x, y, d;
        cin >> x >> y >> d;
        programs[i] = {d, y, x};
    }
    sort(programs.begin(), programs.end());

    map<long long, long long> mp;
    long long S = 0;
    long long C = 0;

    for (int i = 0; i < n; ++i) {
        long long d = get<0>(programs[i]);
        long long y = get<1>(programs[i]);
        long long x = get<2>(programs[i]);

        if (y == 0) {
            C += x;
            continue;
        }

        while (x > 0) {
            long long k = 0;
            if (d > S) {
                k = (d - S) / y;
            }
            if (k > 0) {
                k = min(k, x);
                S += k * y;
                C += k;
                mp[y] += k;
                x -= k;
            } else {
                if (mp.empty()) break;
                auto it = mp.rbegin();
                long long M = it->first;
                if (M <= y) break;
                long long cnt_M = it->second;
                long long r = min(cnt_M, x);
                S = S - r * M + r * y;
                mp[y] += r;
                mp[M] -= r;
                if (mp[M] == 0) {
                    mp.erase(M);
                }
                x -= r;
            }
        }
    }
    cout << C << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
