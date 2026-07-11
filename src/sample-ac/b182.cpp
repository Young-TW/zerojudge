#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    while (cin >> m >> n) {
        long long areas[35];
        int min_x[35], max_x[35], min_y[35], max_y[35];

        for (int i = 0; i < m; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            min_x[i] = min(x1, x2);
            max_x[i] = max(x1, x2);
            min_y[i] = min(y1, y2);
            max_y[i] = max(y1, y2);
            areas[i] = 1LL * (max_x[i] - min_x[i]) * (max_y[i] - min_y[i]);
        }

        for (int i = 0; i < n; ++i) {
            int px, py;
            cin >> px >> py;
            long long total_area = 0;
            for (int j = 0; j < m; ++j) {
                if (px >= min_x[j] && px <= max_x[j] && py >= min_y[j] && py <= max_y[j]) {
                    total_area += areas[j];
                }
            }
            cout << total_area << "\n";
        }
    }

    return 0;
}
