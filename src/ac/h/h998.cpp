#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;
vector<int> p;

void ensure(int n) {
    int old_size = p.size();
    if (old_size > n) return;
    p.resize(n + 1, 0);
    if (old_size == 0) {
        p[0] = 1;
        old_size = 1;
    }
    for (int i = old_size; i <= n; ++i) {
        int sum = 0;
        for (int k = 1; ; ++k) {
            int g1 = k * (3 * k - 1) / 2;
            if (g1 > i) break;
            int g2 = k * (3 * k + 1) / 2;
            
            if (k % 2 == 1) {
                sum += p[i - g1];
                if (sum >= MOD) sum -= MOD;
                if (g2 <= i) {
                    sum += p[i - g2];
                    if (sum >= MOD) sum -= MOD;
                }
            } else {
                sum -= p[i - g1];
                if (sum < 0) sum += MOD;
                if (g2 <= i) {
                    sum -= p[i - g2];
                    if (sum < 0) sum += MOD;
                }
            }
        }
        p[i] = sum;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        ensure(n);
        for (int i = 1; i <= n; ++i) {
            cout << p[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
