#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        vector<long long> a;
        long long x;
        bool terminated = false;
        while (cin >> x) {
            if (x == 0) { terminated = true; break; }
            a.push_back(x);
        }
        if (!terminated) break;

        long long N;
        if (!(cin >> N)) break;

        int n = (int)a.size();
        for (long long d = 0; d < N; ++d) {
            vector<long long> add(n, 0);
            for (int i = 0; i < n; ++i) {
                bool endpoint = (i == 0 || i == n - 1);
                long long give = endpoint ? a[i] / 10 : a[i] / 20;
                if (give == 0) continue;
                if (i > 0 && a[i] > a[i - 1]) add[i - 1] += give;
                if (i < n - 1 && a[i] > a[i + 1]) add[i + 1] += give;
            }
            for (int i = 0; i < n; ++i) a[i] += add[i];
        }

        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}
