#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<int> L(n + 1, -1);
        vector<int> R(n + 1, -1);
        vector<int> bit(2 * n + 2, 0);

        for (int i = 0; i < 2 * n; ++i) {
            int val;
            cin >> val;
            if (L[val] == -1) {
                L[val] = i + 1;
            } else {
                R[val] = i + 1;
            }
        }

        auto add = [&](int idx, int val) {
            for (; idx <= 2 * n; idx += idx & -idx) {
                bit[idx] += val;
            }
        };

        auto query = [&](int idx) {
            int sum = 0;
            for (; idx > 0; idx -= idx & -idx) {
                sum += bit[idx];
            }
            return sum;
        };

        long long total_sum = 0;
        for (int i = 1; i <= n; ++i) {
            int sum = query(R[i] - 1) - query(L[i]);
            total_sum += sum;
            add(L[i], 1);
            add(R[i], 1);
        }

        cout << total_sum << "\n";
    }

    return 0;
}
