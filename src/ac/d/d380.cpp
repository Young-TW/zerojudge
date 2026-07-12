#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    while (cin >> s1 >> s2) {
        if (s1 == "0" || s2 == "0") {
            cout << "0\n";
            continue;
        }

        int n1 = s1.length();
        int n2 = s2.length();
        vector<int> res(n1 + n2, 0);

        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                res[i + j] += (s1[i] - '0') * (s2[j] - '0');
            }
        }

        for (int i = 0; i < n1 + n2 - 1; ++i) {
            if (res[i] >= 10) {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        }

        string ans = "";
        int i = n1 + n2 - 1;
        while (i >= 0 && res[i] == 0) {
            --i;
        }
        while (i >= 0) {
            ans += to_string(res[i]);
            --i;
        }
        cout << ans << "\n";
    }

    return 0;
}
