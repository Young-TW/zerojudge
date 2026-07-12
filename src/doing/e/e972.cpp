#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    while (cin >> n) {
        long long m;
        char c;
        cin >> m >> c;

        long long numerator;
        long long denominator;

        if (c == 'T') {
            numerator = n - m;
            denominator = 1;
        } else if (c == 'U') {
            numerator = 10 * n - 309 * m;
            denominator = 309;
        } else if (c == 'J') {
            numerator = 25 * n - 7 * m;
            denominator = 7;
        } else if (c == 'E') {
            numerator = 2 * n - 69 * m;
            denominator = 69;
        } else {
            continue;
        }

        if (numerator < 0) {
            cout << "No Money\n";
        } else {
            long long scaled = (numerator * 100 + denominator / 2) / denominator;
            long long int_part = scaled / 100;
            long long frac_part = scaled % 100;
            cout << c << " " << int_part << "." << (frac_part < 10 ? "0" : "") << frac_part << "\n";
        }
    }

    return 0;
}
