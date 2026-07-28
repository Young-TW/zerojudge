#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXC = 1000002;               // enough for indices 0 … 1 000 001
    static int diff[MAXC];

    int N;
    while (cin >> N) {
        // reset only the part we will use (full reset is cheap enough)
        memset(diff, 0, sizeof(diff));

        int maxE = 0;
        for (int i = 0; i < N; ++i) {
            int S, E;
            cin >> S >> E;
            ++diff[S];
            --diff[E];
            if (E > maxE) maxE = E;
        }

        int cur = 0, best = 0;
        for (int x = 0; x <= maxE; ++x) {
            cur += diff[x];
            if (cur > best) best = cur;
        }

        if (N == 0) cout << 1 << '\n';
        else        cout << best << '\n';
    }
    return 0;
}
