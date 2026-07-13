#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const string haab_months[] = {
        "pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", 
        "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", 
        "koyab", "cumhu", "uayet"
    };
    const string tzolkin_names[] = {
        "imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", 
        "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", 
        "eznab", "canac", "ahau"
    };

    int n;
    while (cin >> n) {
        cout << n << "\n";
        for (int i = 0; i < n; ++i) {
            int day;
            char dot;
            string month;
            int year;
            cin >> day >> dot >> month >> year;

            int month_index = -1;
            for (int j = 0; j < 19; ++j) {
                if (haab_months[j] == month) {
                    month_index = j;
                    break;
                }
            }

            int total_days = year * 365 + month_index * 20 + day;
            int t_year = total_days / 260;
            int t_days = total_days % 260;
            int t_num = t_days % 13 + 1;
            int t_name_idx = t_days % 20;

            cout << t_num << " " << tzolkin_names[t_name_idx] << " " << t_year << "\n";
        }
    }

    return 0;
}
