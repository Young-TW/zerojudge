#include <iostream>

using namespace std;

const int MAXP = 50000;
int primes[MAXP / 10];
bool is_composite[MAXP + 5];
int prime_count = 0;

long long gcd_ll(long long a, long long b) {
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

void sieve() {
    for (int i = 2; i <= MAXP; ++i) {
        if (!is_composite[i]) {
            primes[prime_count++] = i;
        }
        for (int j = 0; j < prime_count && (long long)i * primes[j] <= MAXP; ++j) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int n;
    while (cin >> n) {
        while (n--) {
            long long a0, a1, b0, b1;
            cin >> a0 >> a1 >> b0 >> b1;
            long long ans = 1;
            long long temp_b1 = b1;
            long long temp_b0 = b0;
            long long temp_a0 = a0;
            long long temp_a1 = a1;

            for (int i = 0; i < prime_count && (long long)primes[i] * primes[i] <= temp_b1; ++i) {
                int p = primes[i];
                if (temp_b1 % p == 0) {
                    int B1 = 0, B0 = 0, A0 = 0, A1 = 0;
                    while (temp_b1 % p == 0) { temp_b1 /= p; B1++; }
                    while (temp_b0 % p == 0) { temp_b0 /= p; B0++; }
                    while (temp_a0 % p == 0) { temp_a0 /= p; A0++; }
                    while (temp_a1 % p == 0) { temp_a1 /= p; A1++; }
                    
                    int cnt = 0;
                    if (A1 < A0 && B1 > B0) {
                        if (A1 == B1) cnt = 1;
                    } else if (A1 < A0 && B1 == B0) {
                        if (A1 <= B1) cnt = 1;
                    } else if (A1 == A0 && B1 > B0) {
                        if (B1 >= A1) cnt = 1;
                    } else if (A1 == A0 && B1 == B0) {
                        if (A1 <= B1) cnt = B1 - A1 + 1;
                    }
                    
                    if (cnt == 0) {
                        ans = 0;
                        break;
                    }
                    ans *= cnt;
                }
            }

            if (ans > 0 && temp_b1 > 1) {
                long long p = temp_b1;
                int B1 = 1, B0 = 0, A0 = 0, A1 = 0;
                while (temp_b0 % p == 0) { temp_b0 /= p; B0++; }
                while (temp_a0 % p == 0) { temp_a0 /= p; A0++; }
                while (temp_a1 % p == 0) { temp_a1 /= p; A1++; }
                
                int cnt = 0;
                if (A1 < A0 && B1 > B0) {
                    if (A1 == B1) cnt = 1;
                } else if (A1 < A0 && B1 == B0) {
                    if (A1 <= B1) cnt = 1;
                } else if (A1 == A0 && B1 > B0) {
                    if (B1 >= A1) cnt = 1;
                } else if (A1 == A0 && B1 == B0) {
                    if (A1 <= B1) cnt = B1 - A1 + 1;
                }
                
                if (cnt == 0) {
                    ans = 0;
                } else {
                    ans *= cnt;
                }
            }
            // x must divide b1, so any prime factor of a1 not dividing b1
            // forces exponent 0, contradicting gcd(x,a0)=a1 -> no solution.
            if (ans > 0) {
                long long r = a1, g;
                while ((g = gcd_ll(r, b1)) > 1) r /= g;
                if (r > 1) ans = 0;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
