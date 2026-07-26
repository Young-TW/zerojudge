#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

string encode(long long x) {
    if (x == 0) return "0";

    string res;
    bool first = true;
    // examine bits from high to low (enough for 64‑bit numbers)
    for (int i = 63; i >= 0; --i) {
        if ((x >> i) & 1LL) {
            if (!first) res += '+';
            first = false;
            if (i == 1) {
                res += "2";
            } else {
                res += "2(" + encode(i) + ")";
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    while (cin >> n) {
        cout << encode(n) << '\n';
    }
    return 0;
}
