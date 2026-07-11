#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, t, n;
    while (cin >> s >> t >> n) {
        int b1 = (t * 20 + 50) / 100;
        int b2 = (t * 40 + 50) / 100;
        int b3 = (t * 60 + 50) / 100;

        int p1 = (s * 70 + 50) / 100;
        int p2 = (s * 80 + 50) / 100;
        int p3 = (s * 90 + 50) / 100;
        int p4 = s;

        int cost = (s * t * 30 + 50) / 100;

        int sold = 0;
        long long income = 0;

        for (int i = 0; i < n; ++i) {
            int m;
            cin >> m;
            int c1 = max(0, min(m, b1 - sold));
            int c2 = max(0, min(m - c1, b2 - sold - c1));
            int c3 = max(0, min(m - c1 - c2, b3 - sold - c1 - c2));
            int c4 = m - c1 - c2 - c3;

            income += (long long)c1 * p1 + (long long)c2 * p2 + (long long)c3 * p3 + (long long)c4 * p4;
            sold += m;
        }

        cout << income - cost << "\n";
    }

    return 0;
}
