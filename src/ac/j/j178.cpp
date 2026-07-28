#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// convert unsigned __int128 to decimal string
string toStringUnsigned(__uint128_t x) {
    if (x == 0) return "0";
    string s;
    while (x > 0) {
        int digit = static_cast<int>(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long M;               // number of monsters
    unsigned long long A;      // initial power
    while (cin >> M >> A) {    // read until EOF
        vector<unsigned long long> t(M);
        for (long long i = 0; i < M; ++i) cin >> t[i];

        __uint128_t cur = A;   // use 128‑bit to avoid overflow
        for (long long i = 0; i < M; ++i) {
            if (cur > t[i]) {
                cur += t[i];
            } else {
                break;
            }
        }
        cout << toStringUnsigned(cur) << '\n';
    }
    return 0;
}
