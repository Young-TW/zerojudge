#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    char slash;
    while (cin >> a >> slash >> b) {
        if (b == 0) continue;

        bool negative = false;
        if (a < 0 && b > 0) negative = true;
        if (a > 0 && b < 0) negative = true;
        
        if (a < 0) a = -a;
        if (b < 0) b = -b;

        string ans;
        if (negative) ans += "-";

        long long int_part = a / b;
        long long rem = a % b;
        ans += to_string(int_part);

        if (rem == 0) {
            cout << ans << "\n";
            continue;
        }

        ans += ".";

        string frac_part;
        map<long long, int> rem_pos;
        int pos = 0;
        int cycle_start = -1;

        while (rem != 0) {
            if (rem_pos.find(rem) != rem_pos.end()) {
                cycle_start = rem_pos[rem];
                break;
            }
            rem_pos[rem] = pos;
            rem *= 10;
            frac_part += to_string(rem / b);
            rem %= b;
            pos++;
        }

        if (cycle_start == -1) {
            ans += frac_part;
        } else {
            ans += frac_part.substr(0, cycle_start);
            ans += "(";
            ans += frac_part.substr(cycle_start);
            ans += ")";
        }
        cout << ans << "\n";
    }
    return 0;
}
