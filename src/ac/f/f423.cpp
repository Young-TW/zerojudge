#include <bits/stdc++.h>
using namespace std;

// print a signed __int128 value
void print_int128(__int128 x) {
    if (x == 0) {
        cout << '0';
        return;
    }
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    string s;
    while (x > 0) {
        int digit = x % 10;
        s.push_back('0' + digit);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long k = (n + 1) / 2;               // count of odd numbers
        __int128 ans = (__int128)k * k;          // k squared
        print_int128(ans);
        cout << '\n';
    }
    return 0;
}
