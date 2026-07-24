#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long double EPS = 1e-12L;

    long long N, R;
    while (cin >> N >> R) {
        vector<pair<long long,long long>> segs;
        long long cannot = 0;               // B
        for (long long i = 0; i < N; ++i) {
            long double x, y;
            cin >> x >> y;
            if (y - (long double)R > EPS) { // y > R  (cannot be covered)
                ++cannot;
                continue;
            }
            long double dx = sqrt((long double)R * (long double)R - y * y);
            long double left  = x - dx;
            long double right = x + dx;
            long long L = (long long)ceil(left - EPS);
            long long RR = (long long)floor(right + EPS);
            if (L > RR) {                    // no integer point inside
                ++cannot;
                continue;
            }
            segs.emplace_back(L, RR);
        }

        sort(segs.begin(), segs.end(),
             [](const pair<long long,long long>& a,
                const pair<long long,long long>& b) {
                 if (a.second != b.second) return a.second < b.second;
                 return a.first < b.first;
             });

        long long stations = 0;              // A
        long long lastPos = LLONG_MIN;       // last placed base station
        for (const auto& p : segs) {
            long long L = p.first, Rr = p.second;
            if (lastPos >= L && lastPos <= Rr) continue; // already covered
            ++stations;
            lastPos = Rr;                     // place at rightmost integer
        }

        cout << stations << ' ' << cannot << '\n';
    }
    return 0;
}
