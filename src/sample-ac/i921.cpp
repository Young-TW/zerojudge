#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            int C, d;
            if (!(cin >> C >> d)) break;
            double ans = C + 5.0 / 9.0 * d;
            cout << "Case " << i << ": " << fixed << setprecision(2) << ans << "\n";
        }
    }
    return 0;
}
