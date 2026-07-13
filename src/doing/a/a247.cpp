#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    vector<int> used(1, 0);
    int test_case = 0;

    while (cin >> N) {
        test_case++;
        if (N >= (int)used.size()) {
            used.resize(N + 1, 0);
        }

        int primitive_count = 0;
        int used_count = 0;

        int limit_m = 1;
        while (limit_m * limit_m <= N) {
            limit_m++;
        }
        limit_m--;

        for (int m = 2; m <= limit_m; ++m) {
            int m2 = m * m;
            for (int n = 1; n < m; ++n) {
                if (((m + n) & 1) && gcd(m, n) == 1) {
                    int n2 = n * n;
                    int z = m2 + n2;
                    if (z <= N) {
                        primitive_count++;
                        int x = m2 - n2;
                        int y = 2 * m * n;
                        for (int k = 1; k * z <= N; ++k) {
                            if (used[k * x] != test_case) {
                                used[k * x] = test_case;
                                used_count++;
                            }
                            if (used[k * y] != test_case) {
                                used[k * y] = test_case;
                                used_count++;
                            }
                            if (used[k * z] != test_case) {
                                used[k * z] = test_case;
                                used_count++;
                            }
                        }
                    }
                }
            }
        }

        cout << primitive_count << " " << (N - used_count) << "\n";
    }

    return 0;
}
