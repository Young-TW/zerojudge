#include <iostream>
#include <string>
#include <map>

using namespace std;

int parseTime(const string& s) {
    size_t pos = s.find(':');
    int h = stoi(s.substr(0, pos));
    int m = stoi(s.substr(pos + 1));
    return h * 60 + m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string home, home_time_str;
    while (cin >> home >> home_time_str) {
        int home_min = parseTime(home_time_str);
        map<string, int> diff_map;

        int n;
        if (!(cin >> n)) break;
        for (int i = 0; i < n; ++i) {
            string region, time_str;
            cin >> region >> time_str;
            int region_min = parseTime(time_str);
            diff_map[region] = home_min - region_min;
        }

        int t;
        if (!(cin >> t)) break;
        for (int i = 0; i < t; ++i) {
            string region, time_str;
            cin >> region >> time_str;
            int region_min = parseTime(time_str);
            int result_min = (region_min + diff_map[region]) % 1440;
            if (result_min < 0) {
                result_min += 1440;
            }
            int h = result_min / 60;
            int m = result_min % 60;
            cout << region << " " << time_str << " " << home << " " << h << ":";
            if (m < 10) cout << "0";
            cout << m << "\n";
        }
    }

    return 0;
}
