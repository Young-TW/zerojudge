#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    bool firstCase = true;
    while (T--) {
        int N;
        cin >> N;
        vector<int> t(N), f(N);
        for (int i = 0; i < N; i++) cin >> t[i] >> f[i];

        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;

        sort(idx.begin(), idx.end(), [&](int a, int b) {
            // a before b iff t[a]*f[b] < t[b]*f[a]  (higher fine/time ratio first)
            long long lhs = (long long)t[a] * f[b];
            long long rhs = (long long)t[b] * f[a];
            if (lhs != rhs) return lhs < rhs;
            return a < b; // tie: lexicographically smallest (lower index first)
        });

        if (!firstCase) cout << "\n";
        firstCase = false;
        for (int i = 0; i < N; i++) {
            if (i) cout << " ";
            cout << (idx[i] + 1);
        }
        cout << "\n";
    }
    return 0;
}
