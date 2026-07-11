#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

long long gcd_ll(long long a, long long b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

vector<int> sieve_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

pair<long long, long long> simplify_sqrt(long long D, const vector<int>& primes) {
    long long s = 1;
    long long r = 1;
    long long temp = D;
    for (int p : primes) {
        if (1LL * p * p > temp) break;
        if (temp % p == 0) {
            int cnt = 0;
            while (temp % p == 0) {
                temp /= p;
                cnt++;
            }
            for (int i = 0; i < cnt / 2; ++i) s *= p;
            if (cnt % 2 == 1) r *= p;
        }
    }
    if (temp > 1) r *= temp;
    return make_pair(s, r);
}

pair<long long, long long> simplify_frac(long long num, long long den) {
    long long g = gcd_ll(num, den);
    num /= g;
    den /= g;
    if (den < 0) {
        num = -num;
        den = -den;
    }
    return make_pair(num, den);
}

string format_rational(long long num, long long den) {
    if (den == 1) return to_string(num);
    else return to_string(num) + "/" + to_string(den);
}

string format_irrational_numerator(long long A, long long B, long long r) {
    string res;
    if (A != 0) {
        res += to_string(A);
    }
    res += "±";
    if (B != 1) {
        res += to_string(B);
    }
    res += "√";
    res += to_string(r);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> primes = sieve_primes(25000);

    int t;
    if (!(cin >> t)) return 0;
    for (int tc = 0; tc < t; ++tc) {
        int n;
        cin >> n;
        for (int q = 1; q <= n; ++q) {
            long long a, b, c;
            cin >> a >> b >> c;
            long long D = b * b - 4 * a * c;
            string prefix = to_string(q) + ". ";
            if (D < 0) {
                cout << prefix << "無解\n";
            } else if (D == 0) {
                long long num = -b;
                long long den = 2 * a;
                pair<long long, long long> frac = simplify_frac(num, den);
                cout << prefix << format_rational(frac.first, frac.second) << " (重根)\n";
            } else {
                long long sqrt_D = sqrt((long double)D);
                while (sqrt_D * sqrt_D < D) ++sqrt_D;
                while (sqrt_D * sqrt_D > D) --sqrt_D;
                if (sqrt_D * sqrt_D == D) {
                    long long den = 2 * a;
                    long long num1 = -b + sqrt_D;
                    long long num2 = -b - sqrt_D;
                    pair<long long, long long> frac1 = simplify_frac(num1, den);
                    pair<long long, long long> frac2 = simplify_frac(num2, den);
                    long long n1 = frac1.first, d1 = frac1.second;
                    long long n2 = frac2.first, d2 = frac2.second;
                    if (n1 * d2 < n2 * d1) {
                        swap(n1, n2);
                        swap(d1, d2);
                    }
                    cout << prefix << format_rational(n1, d1) << " 或 " << format_rational(n2, d2) << "\n";
                } else {
                    pair<long long, long long> sr = simplify_sqrt(D, primes);
                    long long s = sr.first, r = sr.second;
                    long long A, B, Den;
                    if (2 * a > 0) {
                        A = -b;
                        B = s;
                        Den = 2 * a;
                    } else {
                        A = b;
                        B = s;
                        Den = -2 * a;
                    }
                    long long g = gcd_ll(A, B);
                    g = gcd_ll(g, Den);
                    A /= g; B /= g; Den /= g;
                    if (Den < 0) {
                        A = -A; B = -B; Den = -Den;
                    }
                    if (B < 0) B = -B;
                    string num_str = format_irrational_numerator(A, B, r);
                    if (Den == 1) {
                        cout << prefix << num_str << "\n";
                    } else {
                        cout << prefix << "分母" << Den << "\n";
                        cout << string(prefix.length(), ' ') << "分子" << num_str << "\n";
                    }
                }
            }
        }
    }
    return 0;
}
