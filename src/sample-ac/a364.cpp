#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int C(int m, int n) {
    if (m < n) return 0;
    if (n == 0 || n == m) return 1;
    if (n == 1 || n == m - 1) return m;
    if (n == 2) return m * (m - 1) / 2;
    if (n == 3) return m * (m - 1) * (m - 2) / 6;
    return 0;
}

void solve(int N) {
    int a = 2, b = 1, c = 0;
    int min_a = 100, min_b = 100, min_c = 100;
    bool found = false;

    for (a = 2; a <= 20; ++a) {
        for (b = 1; b < a; ++b) {
            for (c = 0; c < b; ++c) {
                if (C(a, 3) + C(b, 2) + C(c, 1) == N) {
                    if (a < min_a || (a == min_a && b < min_b) || (a == min_a && b == min_b && c < min_c)) {
                        min_a = a;
                        min_b = b;
                        min_c = c;
                        found = true;
                    }
                }
            }
        }
    }

    if (found) {
        cout << min_a << min_b << min_c << endl;
    } else {
        cout << "000" << endl;
    }
}

int main() {
    int m;
    cin >> m;
    vector<int> nums(m);
    for (int i = 0; i < m; ++i) {
        cin >> nums[i];
    }

    for (int i = 0; i < m; ++i) {
        solve(nums[i]);
    }

    return 0;
}
