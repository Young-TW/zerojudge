#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<string> v;
        string suits = "SHDF";
        string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                v.push_back(string(1, suits[i]) + ranks[j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            int cmd;
            cin >> cmd;
            if (cmd == 1) {
                int a, b;
                cin >> a >> b;
                rotate(v.begin(), v.begin() + a - 1, v.end());
                rotate(v.begin() + (b - a + 1), v.begin() + (52 - a + 1), v.end());
            } else if (cmd == 2) {
                int a, b;
                cin >> a >> b;
                rotate(v.begin(), v.begin() + a - 1, v.begin() + b);
                rotate(v.begin(), v.begin() + (b - a + 1), v.end());
            } else if (cmd == 3) {
                int k;
                cin >> k;
                rotate(v.begin(), v.end() - k, v.end());
            } else if (cmd == 4) {
                int k;
                cin >> k;
                rotate(v.begin(), v.begin() + k, v.end());
            }
        }

        for (int i = 0; i < 5; ++i) {
            if (i > 0) cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    return 0;
}
