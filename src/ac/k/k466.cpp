#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        long long bestP = -1, bestR = -1;
        int bestPi = -1, bestRi = -1;
        for (int i = 1; i <= n; i++) {
            long long prev = 0, cur = 0;
            long long up = 0, down = 0;
            for (int j = 0; j < m; j++) {
                cin >> cur;
                if (j > 0) {
                    long long diff = cur - prev;
                    if (diff > 0) up += diff;
                    else down += -diff;
                }
                prev = cur;
            }
            if (up > bestP) { bestP = up; bestPi = i; }
            if (down > bestR) { bestR = down; bestRi = i; }
        }
        cout << bestPi << "\n" << bestRi << "\n";
    }
    return 0;
}
