// c096 / UVa 700 - Date Bugs
// Self-written solution.
// Each computer i wraps display with period p_i = b_i - a_i, so the real year z
// satisfies z ≡ y_i (mod p_i). Find the smallest z >= u = max{a_i}, z < 10000,
// meeting every congruence. Search is bounded by 10000 * n <= 200000 ops/case.
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int caseNo = 0;
    while (std::cin >> n) {
        if (n == 0) break;

        std::vector<int> y(n), a(n), b(n);
        int U = 0;                     // max a_i
        for (int i = 0; i < n; ++i) {
            std::cin >> y[i] >> a[i] >> b[i];
            if (a[i] > U) U = a[i];
        }

        int answer = -1;               // -1 means not found
        for (int year = U; year < 10000; ++year) {
            bool ok = true;
            for (int i = 0; i < n; ++i) {
                int period = b[i] - a[i];              // > 0 since a_i < b_i
                // year >= U >= a_i and y_i >= a_i, so both are non-negative
                if ((year - a[i]) % period != (y[i] - a[i]) % period) {
                    ok = false;
                    break;
                }
            }
            if (ok) { answer = year; break; }          // smallest year found
        }

        ++caseNo;
        if (caseNo > 1) std::cout << "\n";             // blank line BETWEEN cases
        std::cout << "Case #" << caseNo << ":\n";
        if (answer != -1) {
            std::cout << "The actual year is " << answer << ".\n";
        } else {
            std::cout << "Unknown bugs detected.\n";
        }
    }
    return 0;
}
