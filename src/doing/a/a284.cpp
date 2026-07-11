#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y;
        }

        if (n < 4) {
            cout << fixed;
            cout.precision(6);
            cout << 3.0 << "\n";
            continue;
        }

        long long total_C = 0;
        vector<Point> other(n - 1);

        for (int i = 0; i < n; ++i) {
            Point P = pts[i];
            int idx = 0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    other[idx++] = pts[j];
                }
            }
            sort(other.begin(), other.end(), [&](const Point& A, const Point& B) {
                long long c = cross(P, A, B);
                if (c != 0) return c > 0;
                long long distA = (A.x - P.x) * (A.x - P.x) + (A.y - P.y) * (A.y - P.y);
                long long distB = (B.x - P.x) * (B.x - P.x) + (B.y - P.y) * (B.y - P.y);
                return distA < distB;
            });

            long long sum_not_contain = 0;
            int j = 1;
            for (int k = 0; k < n - 1; ++k) {
                if (j <= k) j = k + 1;
                while (j < k + n - 1) {
                    Point A = other[k];
                    Point B = other[j % (n - 1)];
                    if (cross(P, A, B) > 0) {
                        j++;
                    } else {
                        break;
                    }
                }
                int cnt = j - k - 1;
                sum_not_contain += (long long)cnt * (cnt - 1) / 2;
            }
            long long C_P = (long long)(n - 1) * (n - 2) * (n - 3) / 6 - sum_not_contain;
            total_C += C_P;
        }

        long long C4 = (long long)n * (n - 1) * (n - 2) * (n - 3) / 24;
        long long convex_quad = C4 - total_C;
        long long total_inside = C4 + convex_quad;

        long long C3 = (long long)n * (n - 1) * (n - 2) / 6;
        double ans = 3.0 + (double)total_inside / C3;

        cout << fixed;
        cout.precision(6);
        cout << ans << "\n";
    }

    return 0;
}
