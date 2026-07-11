#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x0, y0, L0, R;
    while (cin >> x0 >> y0 >> L0 >> R) {
        int N;
        cin >> N;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int xi, yi, Li;
            cin >> xi >> yi >> Li;
            int dx = xi - x0;
            int dy = yi - y0;
            if (dx * dx + dy * dy <= R * R && Li <= L0) {
                ans++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
