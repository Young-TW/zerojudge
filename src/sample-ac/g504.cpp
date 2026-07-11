#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long y;
    while (cin >> N >> y) {
        long long first_t = -1;
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            long long t, x;
            cin >> t >> x;
            if (i == 0) {
                first_t = t;
            }
            long long T = first_t + y;
            if (t <= T) {
                long long remaining = x - (T - t);
                if (remaining > 0) {
                    ans += remaining;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
