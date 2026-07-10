#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        if (s == "0") break;
        long long r = 0;
        for (char c : s) {
            r = (r * 10 + (c - '0')) % 17;
        }
        cout << (r == 0 ? 1 : 0) << "\n";
    }
    return 0;
}
