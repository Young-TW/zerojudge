#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int days_in_month[13] =
        {0,31,28,31,30,31,30,31,31,30,31,30,31};

    int N;
    while (cin >> N) {
        while (N--) {
            int W, M, D;
            cin >> W >> M >> D;

            // 1. day of year
            int day_of_year = D;
            for (int i = 1; i < M; ++i) day_of_year += days_in_month[i];

            // 2. weekday of the date (1 = Mon ... 7 = Sun)
            int weekday = ((W - 1) + (day_of_year - 1)) % 7 + 1;

            // 5. raw week number (weeks counted from the nearest Monday to Jan 1)
            int week_raw = (day_of_year - weekday + 10) / 7;   // integer division

            int week;
            if (week_raw == 0) week = -1;          // previous year's last week
            else               week = week_raw;    // current year (may be 53)

            cout << week << ' ' << weekday << '\n';
        }
    }
    return 0;
}
