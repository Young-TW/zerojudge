#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L;
    string s;
    const double unitPrice[6] = {0.0, 1.32 * 1 + 1.07,
                                   1.32 * 2 + 1.07,
                                   1.32 * 3 + 1.07,
                                   1.32 * 4 + 1.07,
                                   1.32 * 5 + 1.07};

    while (cin >> L) {
        if (!(cin >> s)) break;
        vector<int> zero;
        zero.reserve(L);
        for (int i = 0; i < L; ++i)
            if (s[i] == '0') zero.push_back(i);

        if (zero.empty()) {
            cout << "0.00 5\n";
            continue;
        }

        double bestCost = 1e100;
        int bestN = 0;

        for (int N = 1; N <= 5; ++N) {
            int cnt = 0;
            size_t idx = 0;
            const int leftShift = N - 1;
            while (idx < zero.size()) {
                int left = zero[idx];
                int centre = left + leftShift;
                if (centre > L - 1) centre = L - 1;
                int right = centre + leftShift;          // may exceed L-1
                ++cnt;
                while (idx < zero.size() && zero[idx] <= right) ++idx;
            }
            double total = cnt * unitPrice[N];
            if (total < bestCost - 1e-9) {
                bestCost = total;
                bestN = N;
            } else if (fabs(total - bestCost) <= 1e-9 && N > bestN) {
                bestN = N;
            }
        }

        // rounding to two decimals (printf does it)
        cout.setf(ios::fixed);
        cout << setprecision(2) << bestCost << ' ' << bestN << '\n';
    }
    return 0;
}
