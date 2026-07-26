#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-12L;

struct Seg {
    long double x1, y1, x2, y2;   // original order (x1 may be > x2)
    long double xl, xr;           // xl <= xr
    long double a;                // slope
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while ( (cin >> n) ) {
        vector<Seg> segs;
        segs.reserve(n);
        for (int i = 0; i < n; ++i) {
            long double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Seg s;
            s.x1 = x1; s.y1 = y1; s.x2 = x2; s.y2 = y2;
            s.id = i;
            if (x1 < x2) {
                s.xl = x1; s.xr = x2;
            } else {
                s.xl = x2; s.xr = x1;
                swap(s.x1, s.x2);
                swap(s.y1, s.y2);
            }
            s.a = (s.y2 - s.y1) / (s.x2 - s.x1);   // safe, denominator != 0
            segs.push_back(s);
        }

        vector<long double> xs;
        xs.reserve(n * (n + 1) / 2 + 5);
        for (auto &s : segs) {
            xs.push_back(s.xl);
            xs.push_back(s.xr);
        }

        // pairwise intersections
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                const Seg &A = segs[i];
                const Seg &B = segs[j];
                if (fabsl(A.a - B.a) < EPS) continue; // parallel
                // line: y = a*x + b   where b = y1 - a*x1
                long double bA = A.y1 - A.a * A.x1;
                long double bB = B.y1 - B.a * B.x1;
                long double x = (bB - bA) / (A.a - B.a);
                if (x + EPS < max(A.xl, B.xl) || x - EPS > min(A.xr, B.xr))
                    continue; // outside overlap
                xs.push_back(x);
            }
        }

        sort(xs.begin(), xs.end());
        vector<long double> uniq;
        uniq.reserve(xs.size());
        for (size_t i = 0; i < xs.size(); ++i) {
            if (i == 0 || fabsl(xs[i] - xs[i-1]) > EPS)
                uniq.push_back(xs[i]);
        }
        xs.swap(uniq);

        // for each elementary interval store the id of the segment that is minimal
        vector<int> bestSeg;   // same size as number of intervals
        bestSeg.reserve(xs.size());

        for (size_t k = 0; k + 1 < xs.size(); ++k) {
            long double l = xs[k], r = xs[k+1];
            if (r - l < EPS) {   // zero length, ignore
                bestSeg.push_back(-1);
                continue;
            }
            long double mid = (l + r) * 0.5L;
            int bestId = -1;
            long double bestY = numeric_limits<long double>::infinity();
            for (const auto &s : segs) {
                if (mid + EPS < s.xl || mid - EPS > s.xr) continue;
                long double y = s.y1 + s.a * (mid - s.x1);
                if (y < bestY) {
                    bestY = y;
                    bestId = s.id;
                }
            }
            bestSeg.push_back(bestId); // -1 means gap
        }

        // count runs of the same id, ignoring gaps
        int cnt = 0;
        int prev = -2; // -2 = gap / none
        for (int id : bestSeg) {
            if (id == -1) {
                prev = -2;
            } else {
                if (id != prev) ++cnt;
                prev = id;
            }
        }

        cout << cnt << "\n";
    }
    return 0;
}
