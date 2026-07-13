#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;
int min_z[MAXN + 1];
int pref[MAXN + 1];
int ans1[MAXN + 1];

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i <= MAXN; ++i) {
        min_z[i] = MAXN + 1;
    }

    for (int m = 2; m * m + 1 <= MAXN; ++m) {
        for (int n = 1; n < m; ++n) {
            if ((m - n) % 2 == 1 && gcd(m, n) == 1) {
                int x = m * m - n * n;
                int y = 2 * m * n;
                int z = m * m + n * n;
                if (z > MAXN) continue;
                
                ans1[z]++;
                
                for (int k = 1; k * z <= MAXN; ++k) {
                    int kx = k * x;
                    int ky = k * y;
                    int kz = k * z;
                    if (kz < min_z[kx]) min_z[kx] = kz;
                    if (kz < min_z[ky]) min_z[ky] = kz;
                    if (kz < min_z[kz]) min_z[kz] = kz;
                }
            }
        }
    }

    for (int v = 1; v <= MAXN; ++v) {
        if (min_z[v] <= MAXN) {
            int T = max(v, min_z[v]);
            pref[T]++;
        }
    }

    for (int i = 1; i <= MAXN; ++i) {
        pref[i] += pref[i - 1];
        ans1[i] += ans1[i - 1];
    }

    int N;
    while (cin >> N) {
        cout << ans1[N] << " " << (N - pref[N]) << "\n";
    }

    return 0;
}
