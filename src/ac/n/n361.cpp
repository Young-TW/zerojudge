#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    long long N;
    while (cin >> N) {
        for (long long i = 0; i < N; i++) {
            long long tmp;
            cin >> tmp;
            int ans;
            if (tmp % 6 == 0) {
                ans = 1;
            } else if (tmp % 2 != 0 && tmp % 3 != 0) {
                ans = 2;
            } else {
                long long s = (long long)sqrt((long double)tmp);
                while (s * s > tmp) s--;
                while ((s + 1) * (s + 1) <= tmp) s++;
                if (s * s == tmp || (tmp % 7 != 0 && tmp % 2 == 0)) ans = 3;
                else ans = 0;
            }
            cout << ans;
            if (i + 1 < N) cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
