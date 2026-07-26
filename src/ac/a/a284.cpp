#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

inline int64 C2(int64 x) { return x * (x - 1) / 2; }
inline int64 C3(int64 x) { return x * (x - 1) * (x - 2) / 6; }
inline int64 C4(int64 x) { return x * (x - 1) * (x - 2) * (x - 3) / 24; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> X(n), Y(n);
        for (int i = 0; i < n; ++i) cin >> X[i] >> Y[i];

        if (n < 3) {
            cout << fixed << setprecision(6) << 0.0 << "\n";
            continue;
        }

        const double PI = acos(-1.0);
        const double EPS = 1e-12;

        int64 total_not_containing = 0;          // Σ_i Σ_start C(k,2)

        vector<double> ang;
        ang.reserve(2 * (n - 1));

        for (int i = 0; i < n; ++i) {
            ang.clear();
            for (int j = 0; j < n; ++j) if (j != i) {
                double a = atan2((double)(Y[j] - Y[i]), (double)(X[j] - X[i]));
                ang.push_back(a);
            }
            sort(ang.begin(), ang.end());
            int m = n - 1;
            for (int k = 0; k < m; ++k) ang.push_back(ang[k] + 2 * PI);

            int r = 0;
            for (int l = 0; l < m; ++l) {
                if (r < l + 1) r = l + 1;
                while (r < l + m && ang[r] - ang[l] < PI - EPS) ++r;
                int64 cnt = r - l - 1;          // points strictly between l and r
                if (cnt >= 2) total_not_containing += cnt * (cnt - 1) / 2;
            }
        }

        int64 Cn3 = C3(n);
        int64 Cn4 = C4(n);
        int64 term1 = (int64)n * C2(n - 1);          // n * C(n-1,2)

        int64 total_triangles_without_center = total_not_containing;
        int64 total_triangles_all = (int64)n * C3(n - 1);
        int64 NC = total_triangles_all - total_triangles_without_center; // Lemma 5

        int64 total_sum = term1 + 2 * Cn4 - NC;     // Lemma 6

        double answer = (double)total_sum / (double)Cn3;
        cout << fixed << setprecision(6) << answer << "\n";
    }
    return 0;
}
