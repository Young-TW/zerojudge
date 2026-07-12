#include <iostream>
#include <algorithm>

using namespace std;

int get_max_prime_factor(int x) {
    int res = 1;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            res = i;
        }
    }
    if (x > 1) res = x;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        int best_val = 0;
        int best_mpf = -1;
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            int mpf = get_max_prime_factor(val);
            if (mpf > best_mpf || (mpf == best_mpf && val > best_val)) {
                best_mpf = mpf;
                best_val = val;
            }
        }
        cout << best_val << "\n";
    }
    return 0;
}
