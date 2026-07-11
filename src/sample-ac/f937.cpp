#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long modpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long n, m;
            cin >> n >> m;
            long long g = gcd(n, m);
            n /= g;
            m /= g;
            
            int cnt2 = 0, cnt5 = 0;
            while (m % 2 == 0) {
                m /= 2;
                cnt2++;
            }
            while (m % 5 == 0) {
                m /= 5;
                cnt5++;
            }
            int a = max(cnt2, cnt5);
            
            long long b = 0;
            if (m > 1) {
                long long k = m;
                long long phi = k;
                long long temp = k;
                
                if (temp % 2 == 0) {
                    while (temp % 2 == 0) temp /= 2;
                    phi /= 2;
                }
                for (long long i = 3; i * i <= temp; i += 2) {
                    if (temp % i == 0) {
                        while (temp % i == 0) temp /= i;
                        phi = phi / i * (i - 1);
                    }
                }
                if (temp > 1) {
                    phi = phi / temp * (temp - 1);
                }
                
                vector<long long> factors;
                temp = phi;
                if (temp % 2 == 0) {
                    factors.push_back(2);
                    while (temp % 2 == 0) temp /= 2;
                }
                for (long long i = 3; i * i <= temp; i += 2) {
                    if (temp % i == 0) {
                        factors.push_back(i);
                        while (temp % i == 0) temp /= i;
                    }
                }
                if (temp > 1) factors.push_back(temp);
                
                b = phi;
                for (long long p : factors) {
                    while (b % p == 0 && modpow(10, b / p, k) == 1) {
                        b /= p;
                    }
                }
            }
            cout << a << " " << b << "\n";
        }
    }
    return 0;
}
