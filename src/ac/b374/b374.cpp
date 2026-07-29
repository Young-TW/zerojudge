// b374 [福州19中]众数 - self-written solution
// Read N integers (values 1..30000, N up to ~30000 per the errata discussion).
// Output every mode (value with the maximum frequency) in ascending order,
// one per line as "value count" separated by a SINGLE space.
// (The sample output's multiple spaces are a documented problem-statement typo;
//  the judge expects a single space, which is why a 3-space submission got WA.)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {                 // robust for single case / trailing EOF
        static int cnt[30005];
        for (int v = 0; v <= 30001; ++v) cnt[v] = 0;
        int maxv = 0;                 // largest value actually seen
        for (int i = 0; i < n; ++i) {
            long long x;
            if (!(cin >> x)) break;   // robust if N over-counts
            if (x >= 1 && x <= 30000) {
                cnt[x]++;
                if ((int)x > maxv) maxv = (int)x;
            }
        }

        int best = 0;
        for (int v = 1; v <= maxv; ++v)
            if (cnt[v] > best) best = cnt[v];

        string out;
        if (best > 0) {
            for (int v = 1; v <= maxv; ++v) {
                if (cnt[v] == best) {
                    out += to_string(v);
                    out += ' ';
                    out += to_string(best);
                    out += '\n';
                }
            }
        }
        cout << out;
    }
    return 0;
}
