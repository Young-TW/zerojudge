#include <bits/stdc++.h>
using namespace std;

bool isDigit(char c) { return c >= '0' && c <= '9'; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        unordered_set<string> dept;
        for (int i = 0; i < N; ++i) {
            string code;
            cin >> code;
            dept.insert(code);
        }

        int errorCnt = 0;
        for (int i = 0; i < 10; ++i) {
            string id;
            cin >> id;
            bool ok = true;

            if (id.size() != 9) ok = false;
            else {
                if (id[0] != 'B') ok = false;
                else if (!isDigit(id[1]) || !isDigit(id[2])) ok = false;
                else if (!isDigit(id[7]) || !isDigit(id[8])) ok = false;
                else {
                    string sub = id.substr(3, 4);
                    if (dept.find(sub) == dept.end()) ok = false;
                }
            }

            if (ok) cout << "Y\n";
            else {
                cout << "N\n";
                ++errorCnt;
            }
        }

        if (errorCnt == 0) cout << "0\n";
        else if (errorCnt == 10) cout << "1\n";
        else {
            cout << fixed << setprecision(1) << (errorCnt / 10.0) << "\n";
        }
    }
    return 0;
}
