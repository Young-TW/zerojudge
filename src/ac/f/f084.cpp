#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    while (cin >> t) {
        const long long D = 232792560LL; // lcm(1..21)
        while (t--) {
            int n;
            cin >> n;
            long long a[25], b[25];
            for (int i = 1; i <= n + 1; i++) {
                cin >> a[i] >> b[i];
            }
            long long sum_min = 0, sum_max = 0;
            for (int i = 1; i <= n + 1; i++) {
                long long C_num = 1;
                int k = i - 1;
                for (int j = 1; j <= k; j++) {
                    C_num = C_num * (n - j + 1) / j;
                }
                C_num *= (n + 1);
                long long C_den = n + 2 - i;
                long long P = C_num * (D / C_den);
                if ((n + 1 - i) % 2 != 0) P = -P;
                
                long long val_a = P * a[i];
                long long val_b = P * b[i];
                sum_min += min(val_a, val_b);
                sum_max += max(val_a, val_b);
            }
            cout << sum_min / D << " " << sum_max / D << "\n";
        }
    }
    return 0;
}
