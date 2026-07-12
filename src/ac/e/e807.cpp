#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int max_day_sum = -1;
    int max_day = 0;
    int sum_m = 0, sum_a = 0, sum_n = 0, sum_e = 0;

    for (int i = 1; i <= 7; ++i) {
        string sm, sa, sn, se;
        if (!(cin >> sm >> sa >> sn >> se)) break;
        
        auto to_int = [](const string& s) {
            int res = 0;
            for (char c : s) {
                if (c != '.') {
                    res = res * 10 + (c - '0');
                }
            }
            return res;
        };

        int m = to_int(sm);
        int a = to_int(sa);
        int n = to_int(sn);
        int e = to_int(se);

        int day_sum = m + a + n + e;
        if (day_sum > max_day_sum) {
            max_day_sum = day_sum;
            max_day = i;
        }
        sum_m += m;
        sum_a += a;
        sum_n += n;
        sum_e += e;
    }

    cout << max_day << "\n";

    if (sum_m > sum_a && sum_m > sum_n && sum_m > sum_e) {
        cout << "morning\n";
    } else if (sum_a > sum_m && sum_a > sum_n && sum_a > sum_e) {
        cout << "afternoon\n";
    } else if (sum_n > sum_m && sum_n > sum_a && sum_n > sum_e) {
        cout << "night\n";
    } else {
        cout << "early morning\n";
    }

    return 0;
}
