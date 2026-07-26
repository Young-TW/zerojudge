#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // days in each month, index 1..12
    const int daysInMonth[13] = {
        0, // dummy for 0 index
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    auto ordinal = [&](int month, int day) -> int {
        int sum = 0;
        for (int m = 1; m < month; ++m) sum += daysInMonth[m];
        return sum + day;
    };

    int m1, d1, m2, d2;
    while (std::cin >> m1 >> d1 >> m2 >> d2) {
        int start = ordinal(m1, d1);
        int end   = ordinal(m2, d2);
        int D = end - start + 1;          // total rented days (inclusive)
        int free = D / 10;                // free days
        long long cost = static_cast<long long>(D - free) * 100LL;
        std::cout << cost << '\n';
    }
    return 0;
}
