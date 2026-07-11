#include <iostream>
#include <utility>

using namespace std;

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct Frac {
    long long num, den;
    Frac(long long n = 0, long long d = 1) : num(n), den(d) {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long long g = gcd(num, den);
        if (g != 0) {
            num /= g;
            den /= g;
        }
    }
    Frac operator+(const Frac& o) const {
        return Frac(num * o.den + o.num * den, den * o.den);
    }
    Frac operator/(const Frac& o) const {
        return Frac(num * o.den, den * o.num);
    }
};

Frac dp[15][15];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= 10; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = Frac(0, 1);
            } else if (i == 0 || j == 0) {
                dp[i][j] = Frac(1, 1);
            } else {
                dp[i][j] = (dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1]) / Frac(3, 1);
            }
        }
    }

    int x, y;
    while (cin >> x >> y) {
        cout << dp[x][y].num << "/" << dp[x][y].den << "\n";
    }

    return 0;
}
