#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<int> v(n);
        long long total = 0;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            int p = s.find('.');
            int d = 0, c = 0;
            if (p != string::npos) {
                d = atoi(s.substr(0, p).c_str());
                string cs = s.substr(p + 1);
                while (cs.length() < 2) cs += "0";
                c = atoi(cs.c_str());
            } else {
                d = atoi(s.c_str());
            }
            v[i] = d * 100 + c;
            total += v[i];
        }
        long long avg = total / n;
        int rem = total % n;
        sort(v.rbegin(), v.rend());
        long long exchange = 0;
        for (int i = 0; i < n; ++i) {
            int target = avg + (i < rem ? 1 : 0);
            if (v[i] > target) {
                exchange += v[i] - target;
            }
        }
        cout << "$" << exchange / 100 << "." << setfill('0') << setw(2) << exchange % 100 << "\n";
    }
    return 0;
}
