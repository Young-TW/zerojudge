#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<long long>> ans(9);
    for (int n = 2; n <= 8; n += 2) {
        int half = n / 2;
        long long mod = 1;
        for (int i = 0; i < half; ++i) {
            mod *= 10;
        }
        long long max_val = mod - 1;
        long long max_s = 2 * mod;
        long long actual_mod = mod - 1;
        
        for (long long s = 0; s <= max_s; ++s) {
            long long s2 = s * s;
            if ((s2 - s) % actual_mod == 0) {
                long long a = (s2 - s) / actual_mod;
                long long b = s - a;
                if (a >= 0 && a <= max_val && b >= 0 && b <= max_val) {
                    ans[n].push_back(s2);
                }
            }
        }
    }

    int N;
    while (cin >> N) {
        for (size_t i = 0; i < ans[N].size(); ++i) {
            cout << setw(N) << setfill('0') << ans[N][i] << "\n";
        }
    }

    return 0;
}
