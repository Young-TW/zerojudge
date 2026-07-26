#include <iostream>
#include <string>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

const int MAXP = 3162;
int primes[MAXP];
int prime_cnt = 0;
bool is_composite[MAXP + 1] = {false};

void sieve() {
    for (int i = 2; i <= MAXP; ++i) {
        if (!is_composite[i]) {
            primes[prime_cnt++] = i;
            for (int j = i * i; j <= MAXP; j += i) {
                is_composite[j] = true;
            }
        }
    }
}

void factorize(long long val, long long &m, long long &t, long long g, long long h) {
    if (val == 1) return;
    for (int i = 0; i < prime_cnt; ++i) {
        int p = primes[i];
        if ((long long)p * p > val) break;
        if (val % p == 0) {
            long long k = 0;
            while (val % p == 0) {
                val /= p;
                k++;
            }
            long long tot = k * g;
            long long m_exp = tot / h;
            long long t_exp = tot % h;
            for (long long j = 0; j < m_exp; ++j) m *= p;
            for (long long j = 0; j < t_exp; ++j) t *= p;
        }
    }
    if (val > 1) {
        long long tot = g; // k = 1
        long long m_exp = tot / h;
        long long t_exp = tot % h;
        for (long long j = 0; j < m_exp; ++j) m *= val;
        for (long long j = 0; j < t_exp; ++j) t *= val;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    long long a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        long long g1 = gcd(a, b);
        a /= g1; b /= g1;
        long long g2 = gcd(c, d);
        c /= g2; d /= g2;
        
        long long e = a, f = b, g = c, h = d;
        long long m = 1, t = 1, n = 1, u = 1;
        
        factorize(e, m, t, g, h);
        factorize(f, n, u, g, h);
        
        string m_part;
        if (m == n) {
            m_part = "";
        } else if (m % n == 0) {
            m_part = to_string(m / n);
        } else {
            m_part = to_string(m) + "/" + to_string(n);
        }
        
        string t_part;
        if (t == u) {
            t_part = "";
        } else if (t % u == 0) {
            t_part = to_string(t / u);
        } else {
            t_part = to_string(t) + "/" + to_string(u);
        }
        
        if (m_part.empty() && t_part.empty()) {
            cout << "1\n";
        } else if (m_part.empty()) {
            cout << "_/" << h << "(" << t_part << ")\n";
        } else if (t_part.empty()) {
            cout << m_part << "\n";
        } else {
            cout << m_part << "_/" << h << "(" << t_part << ")\n";
        }
    }
    return 0;
}
