#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    if (!(cin >> n)) return 0;          // no input
    
    // digits of π after the decimal point (first 16 are enough)
    const string pi_digits = "1415926535897932";
    
    if (n >= 1 && n <= static_cast<long long>(pi_digits.size()))
        cout << pi_digits[n - 1] << '\n';
    return 0;
}
