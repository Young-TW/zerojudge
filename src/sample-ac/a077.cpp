#include <iostream>
#include <set>
#include <climits>
using namespace std;

typedef long long ll;

// Length squared (up to constant 0.09) for n pieces:
//   L^2 / 0.09 = n^2 * (Vt/n - V0) = Vt*n - V0*n^2
// We maximize g(n) = Vt*n - V0*n^2, a concave parabola peaking at n* = Vt/(2*V0).
// Check floor and ceil of n*; tie (equal g) => output 0.
// Use exact rational comparison to avoid floating point precision issues.

// For a candidate n, validity requires Vt/n - V0 > 0  =>  Vt > V0 * n  =>  n < Vt/V0.
// Compute g(n) = Vt*n - V0*n*n as a signed value (positive while valid).

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll Vt, V0;
    bool first = true;
    while (cin >> Vt >> V0) {
        if (!first) cout << "\n";
        first = false;
        // Optimal real n* = Vt / (2*V0). Candidates: floor and ceil.
        // Careful: Vt/(2*V0) using integer division.
        ll denom = 2 * V0;
        ll nfloor = Vt / denom;          // floor of Vt/(2*V0) for Vt,V0>0
        // Determine ceil: if Vt % denom == 0, ceil == floor; else floor+1.
        ll nceil = (Vt % denom == 0) ? nfloor : nfloor + 1;

        // Gather candidate n values that are >=1 and valid (n*V0 < Vt).
        set<ll> cand;
        for (ll n : {nfloor, nceil}) {
            if (n >= 1 && n * V0 < Vt) cand.insert(n);
        }

        // Edge: if nfloor is 0, also try n=1 explicitly (must still be valid).
        // (Already covered by nceil >= 1 check above.)

        if (cand.empty()) {
            cout << 0 << "\n";
            continue;
        }

        // Evaluate g(n) = Vt*n - V0*n*n for each candidate, pick max.
        // If tie between two candidates -> output 0.
        ll bestN = -1;
        ll bestG = LLONG_MIN;
        bool tie = false;
        for (ll n : cand) {
            ll g = Vt * n - V0 * n * n;
            if (g > bestG) {
                bestG = g;
                bestN = n;
                tie = false;
            } else if (g == bestG) {
                tie = true;
            }
        }

        if (tie) {
            cout << 0 << "\n";
        } else {
            cout << bestN << "\n";
        }
    }
    return 0;
}
