#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    while (cin >> N >> Q) {
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }

        vector<vector<int>> g(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            g[i][i] = a[i];
            for (int j = i + 1; j < N; ++j) {
                g[i][j] = gcd(g[i][j - 1], a[j]);
            }
        }

        while (Q--) {
            int qL, qR;
            cin >> qL >> qR;
            qL--; qR--;

            long long total = 0;
            for (int len = 1; len <= qR - qL + 1; ++len) {
                for (int i = qL; i + len - 1 <= qR; ++i) {
                    int j = i + len - 1;
                    total += g[i][j];
                }
            }
            cout << total << '\n';
        }
    }

    return 0;
}
